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

/*
 * @file GRRLIB_settings.h
 * Inline functions for configuring the GRRLIB settings.
 */

#ifndef GX_BM_SUBTRACT
	/**
	 * Blending type.
	 * libogc revision 4170 fixed a typographical error. GX_BM_SUBSTRACT was renamed GX_BM_SUBTRACT.
	 * But for previous versions this define is needed.
	 */
	#define GX_BM_SUBTRACT GX_BM_SUBSTRACT
#endif

/**
 * Set drawing color.
 * @param color The drawing color to set.
 */
INLINE
void GRRLIB_SetColor(const u32 color) {
	GRRLIB_Settings.color = color;
}

/**
 * Get drawing color.
 * @return The current drawing color.
 */
INLINE
u32 GRRLIB_GetColor(void) {
	return GRRLIB_Settings.color;
}

/**
 * Set point size.
 * @param pointSize The point size to set.
 */
INLINE
void GRRLIB_SetPointSize(const u8 pointSize) {
	GRRLIB_Settings.pointSize = pointSize;

	GX_SetPointSize(pointSize, GX_TO_ZERO);
}

/**
 * Get point size.
 * @return The current point size.
 */
INLINE
u8 GRRLIB_GetPointSize(void) {
	return GRRLIB_Settings.pointSize;
}

/**
 * Set line width.
 * @param lineWidth The line width to set.
 */
INLINE
void GRRLIB_SetLineWidth(const u8 lineWidth) {
	GRRLIB_Settings.lineWidth = lineWidth;

	GX_SetLineWidth(lineWidth, GX_TO_ZERO);
}

/**
 * Get line width.
 * @return The current line width.
 */
INLINE
u8 GRRLIB_GetLineWidth(void) {
	return GRRLIB_Settings.lineWidth;
}

/**
 * Set a blending mode.
 * @param blendmode The blending mode to use (Default: GRRLIB_BLEND_ALPHA).
 */
INLINE
void GRRLIB_SetBlend(const GRRLIB_blendMode blendmode) {
	GRRLIB_Settings.blend = blendmode;
	switch(GRRLIB_Settings.blend) {
		case GRRLIB_BLEND_ALPHA:
			GX_SetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
			break;
		case GRRLIB_BLEND_ADD:
			GX_SetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_DSTALPHA, GX_LO_CLEAR);
			break;
		case GRRLIB_BLEND_SCREEN:
			GX_SetBlendMode(GX_BM_BLEND, GX_BL_SRCCLR, GX_BL_DSTALPHA, GX_LO_CLEAR);
			break;
		case GRRLIB_BLEND_MULTI:
			GX_SetBlendMode(GX_BM_SUBTRACT, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
			break;
		case GRRLIB_BLEND_INV:
			GX_SetBlendMode(GX_BM_BLEND, GX_BL_INVSRCCLR, GX_BL_INVSRCCLR, GX_LO_CLEAR);
			break;
	}
}

/**
 * Get the current blending mode.
 * @return The current blending mode.
 */
INLINE
GRRLIB_blendMode  GRRLIB_GetBlend(void) {
	return GRRLIB_Settings.blend;
}

/**
 * Turn anti-aliasing on/off.
 * @param aa Set to true to enable anti-aliasing (Default: Enabled).
 */
INLINE
void GRRLIB_SetAntiAliasing(const bool aa) {
	GX_SetCopyFilter(aa ? rmode->aa : GX_FALSE, rmode->sample_pattern, GRRLIB_Settings.deflicker ? GX_TRUE : GX_FALSE, rmode->vfilter);

	GRRLIB_Settings.antialias = aa;
}

/**
 * Get current anti-aliasing setting.
 * @return True if anti-aliasing is enabled.
 */
INLINE
bool GRRLIB_GetAntiAliasing(void) {
	return GRRLIB_Settings.antialias;
}

/**
 * Turn deflicker on/off.
 * @param aa Set to true to enable deflicker (Default: Disabled).
 */
INLINE
void GRRLIB_SetDeflicker(const bool deflicker) {
	GX_SetCopyFilter(GRRLIB_Settings.antialias ? rmode->aa : GX_FALSE, rmode->sample_pattern, deflicker ? GX_TRUE : GX_FALSE, rmode->vfilter);

	GRRLIB_Settings.deflicker = deflicker;
}

/**
 * Get current deflicker setting.
 * @return True if deflicker is enabled.
 */
INLINE
bool GRRLIB_GetDeflicker(void) {
	return GRRLIB_Settings.deflicker;
}
