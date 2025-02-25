/*------------------------------------------------------------------------------
Copyright (c) 2009-2022 The GRRLIB Team and HTV04

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
------------------------------------------------------------------------------*/

#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <ogc/conf.h>
#include <stdio.h>
#include <ogc/machine/processor.h>

#include <grrlib-mod.h>
#include "grrlib-mod/GRRLIB_private.h"

#define DEFAULT_FIFO_SIZE (256 * 1024) /**< GX fifo buffer size. */

static void *gp_fifo = NULL;

static bool is_setup = false;  // To control entry and exit

GRRLIB_drawSettings GRRLIB_Settings;
GXRModeObj *GRRLIB_VideoMode;
void *GRRLIB_XFB[2] = {NULL, NULL};
u32 GRRLIB_FB = 0;

Mtx GRRLIB_View2D;
guVector GRRLIB_Axis2D = {0, 0, 1};

/**
 * Initialize GRRLIB. Call this once at the beginning your code.
 * @return A integer representing a code:
 *         -     0 : The operation completed successfully.
 *         -    -1 : Not enough memory is available to initialize GRRLIB.
 *         -    -2 : Failed to initialize the font engine.
 * @see GRRLIB_Exit
 */
int  GRRLIB_Init (void) {
	f32 yscale;
	u32 xfbHeight;
	Mtx44 perspective;
	s8 error_code = 0;

	// Ensure this function is only ever called once
	if (is_setup == true) {
		return 0;
	}

	// Initialise the video subsystem
	VIDEO_Init();
	VIDEO_SetBlack(true);  // Disable video output during initialisation

	// Grab a pointer to the video mode attributes
	GRRLIB_VideoMode = VIDEO_GetPreferredMode(NULL);
	if (GRRLIB_VideoMode == NULL) {
		return -1;
	}

	// Video Mode Correction
	switch (GRRLIB_VideoMode->viTVMode) {
		case VI_DEBUG_PAL:  // PAL 50hz 576i
			//GRRLIB_VideoMode = &TVPal574IntDfScale;
			GRRLIB_VideoMode = &TVPal528IntDf; // BC ...this is still wrong, but "less bad" for now
			break;
		default:
#ifdef HW_DOL
			if(VIDEO_HaveComponentCable()) {
				GRRLIB_VideoMode = &TVNtsc480Prog;
			}
#endif
			break;
	}

#if defined(HW_RVL)
	// 16:9 and 4:3 Screen Adjustment for Wii
	if (CONF_GetAspectRatio() == CONF_ASPECT_16_9) {
		GRRLIB_VideoMode->viWidth = 678;
	} else {    // 4:3
		GRRLIB_VideoMode->viWidth = 672;
	}
	// This probably needs to consider PAL
	GRRLIB_VideoMode->viXOrigin = (VI_MAX_WIDTH_NTSC - GRRLIB_VideoMode->viWidth) / 2;
#endif

#if defined(HW_RVL)
	 // Patch widescreen on Wii U
	if (CONF_GetAspectRatio() == CONF_ASPECT_16_9 && (*(u32*)(0xCD8005A0) >> 16) == 0xCAFE)
	{
		write32(0xd8006a0, 0x30000004);
		mask32(0xd8006a8, 0, 2);
	}
#endif

	// --
	VIDEO_Configure(GRRLIB_VideoMode);

	// Get some memory to use for a "double buffered" frame buffer
	if ( !(GRRLIB_XFB[0] = MEM_K0_TO_K1(SYS_AllocateFramebuffer(GRRLIB_VideoMode))) ) {
		return -1;
	}
	if ( !(GRRLIB_XFB[1] = MEM_K0_TO_K1(SYS_AllocateFramebuffer(GRRLIB_VideoMode))) ) {
		return -1;
	}

	VIDEO_SetNextFramebuffer(GRRLIB_XFB[GRRLIB_FB]);  // Choose a frame buffer to start with

	VIDEO_Flush();                      // flush the frame to the TV
	VIDEO_WaitVSync();                  // Wait for the TV to finish updating
	// If the TV image is interlaced it takes two passes to display the image
	if (GRRLIB_VideoMode->viTVMode & VI_NON_INTERLACE) {
		VIDEO_WaitVSync();
	}

	// The FIFO is the buffer the CPU uses to send commands to the GPU
	if ( !(gp_fifo = memalign(32, DEFAULT_FIFO_SIZE)) ) {
		return -1;
	}
	memset(gp_fifo, 0, DEFAULT_FIFO_SIZE);
	GX_Init(gp_fifo, DEFAULT_FIFO_SIZE);

	// Clear the background to opaque black and clears the z-buffer
	GX_SetCopyClear((GXColor){ 0, 0, 0, 0 }, GX_MAX_Z24);

	if (GRRLIB_VideoMode->aa) {
		GX_SetPixelFmt(GX_PF_RGB565_Z16, GX_ZC_LINEAR);  // Set 16 bit RGB565
	}
	else {
		GX_SetPixelFmt(GX_PF_RGB8_Z24  , GX_ZC_LINEAR);  // Set 24 bit Z24
	}

	// Other GX setup
	yscale    = GX_GetYScaleFactor(GRRLIB_VideoMode->efbHeight, GRRLIB_VideoMode->xfbHeight);
	xfbHeight = GX_SetDispCopyYScale(yscale);
	GX_SetDispCopySrc(0, 0, GRRLIB_VideoMode->fbWidth, GRRLIB_VideoMode->efbHeight);
	GX_SetDispCopyDst(GRRLIB_VideoMode->fbWidth, xfbHeight);
	GX_SetCopyFilter(GRRLIB_VideoMode->aa, GRRLIB_VideoMode->sample_pattern, GX_FALSE, GRRLIB_VideoMode->vfilter); // Anti-aliasing and deflicker are set to true by default
	GX_SetFieldMode(GRRLIB_VideoMode->field_rendering, ((GRRLIB_VideoMode->viHeight == 2 * GRRLIB_VideoMode->xfbHeight) ? GX_ENABLE : GX_DISABLE));

	GX_SetDispCopyGamma(GX_GM_1_0);

	if (GRRLIB_VideoMode->fbWidth <= 0) { printf("GRRLIB " GRRLIB_VER_STRING); }

	// Setup the vertex descriptor
	GX_ClearVtxDesc();      // clear all the vertex descriptors
	GX_InvVtxCache();       // Invalidate the vertex cache
	GX_InvalidateTexAll();  // Invalidate all textures

	// Tells the flipper to expect direct data
	GX_SetVtxDesc(GX_VA_TEX0, GX_NONE);
	GX_SetVtxDesc(GX_VA_POS,  GX_DIRECT);
	GX_SetVtxDesc(GX_VA_CLR0, GX_DIRECT);

	GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS,  GX_POS_XYZ,  GX_F32, 0);
	GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST,   GX_F32, 0);
	// Colour 0 is 8bit RGBA format
	GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
	GX_SetZMode(GX_FALSE, GX_LEQUAL, GX_TRUE);

	GX_SetNumChans(1);    // colour is the same as vertex colour
	GX_SetNumTexGens(1);  // One texture exists
	GX_SetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
	GX_SetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
	GX_SetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);

	// Default matrix settings, reflected in GRRLIB_Origin()
	guMtxIdentity(GRRLIB_View2D);
	guMtxTransApply(GRRLIB_View2D, GRRLIB_View2D, 0.0, 0.0, -100.0);

	GX_LoadPosMtxImm(GRRLIB_View2D, GX_PNMTX0);

	guOrtho(perspective, 0.0f, GRRLIB_VideoMode->efbHeight, 0.0f, GRRLIB_VideoMode->fbWidth, 0.0f, 1000.0f);
	GX_LoadProjectionMtx(perspective, GX_ORTHOGRAPHIC);

	GX_SetViewport(0.0f, 0.0f, GRRLIB_VideoMode->fbWidth, GRRLIB_VideoMode->efbHeight, 0.0f, 1.0f);
	GX_SetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
	GX_SetAlphaUpdate(GX_TRUE);
	GX_SetAlphaCompare(GX_GREATER, 0, GX_AOP_AND, GX_ALWAYS, 0);
	GX_SetColorUpdate(GX_ENABLE);
	GX_SetCullMode(GX_CULL_NONE);
	GX_SetClipMode(GX_CLIP_ENABLE);
	GRRLIB_ResetScissor();

	// Default settings
	GRRLIB_Settings.color     = 0xFFFFFFFF;
	GRRLIB_Settings.antialias = true;
	GRRLIB_Settings.deflicker = true;
	GRRLIB_Settings.lights    = 0;

	GRRLIB_SetPointSize(6);
	GRRLIB_SetLineWidth(6);
	GRRLIB_SetBlend(GRRLIB_BLEND_ALPHA);

	// Schedule cleanup for when program exits
	is_setup = true;
	atexit(GRRLIB_Exit);

	// Initialise TTF
	if (GRRLIB_InitTTF() != 0) {
		error_code = -2;
	}

	VIDEO_SetBlack(false);  // Enable video output
	return error_code;
}

/**
 * Call this before exiting your application.
 * Ensure this function is only ever called once
 * and only if the setup function has been called.
 */
void  GRRLIB_Exit (void) {
	static  bool  done = false;
	if (done == true || is_setup == false) {
		return;
	}
	else {
		done = true;
	}

	// Allow write access to the full screen
	GX_SetClipMode( GX_CLIP_DISABLE );
	GX_SetScissor( 0, 0, GRRLIB_VideoMode->fbWidth, GRRLIB_VideoMode->efbHeight );

	// We empty both frame buffers on our way out
	// otherwise dead frames are sometimes seen when starting the next app
	GRRLIB_FillScreen( 0x000000FF );  GRRLIB_Render();
	GRRLIB_FillScreen( 0x000000FF );  GRRLIB_Render();

	// Shut down the GX engine
	GX_DrawDone();
	GX_AbortFrame();

	// Free up memory allocated for frame buffers & FIFOs
	if (GRRLIB_XFB[0] != NULL) {
		free(MEM_K1_TO_K0(GRRLIB_XFB[0]));
		GRRLIB_XFB[0] = NULL;
	}
	if (GRRLIB_XFB[1] != NULL) {
		free(MEM_K1_TO_K0(GRRLIB_XFB[1]));
		GRRLIB_XFB[1] = NULL;
	}
	if (gp_fifo != NULL) {
		free(gp_fifo);
		gp_fifo = NULL;
	}

	// Done with TTF
	GRRLIB_ExitTTF();
}
