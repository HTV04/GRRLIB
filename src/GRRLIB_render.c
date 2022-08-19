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

#include <math.h>

#include <grrlib-mod.h>

/**
 * Draw a texture.
 * @param xPos Specifies the x-coordinate of the upper-left corner.
 * @param yPos Specifies the y-coordinate of the upper-left corner.
 * @param tex The texture to draw.
 * @param degrees Angle of rotation.
 * @param scaleX Specifies the x-coordinate scale. -1 could be used for flipping the texture horizontally.
 * @param scaleY Specifies the y-coordinate scale. -1 could be used for flipping the texture vertically.
 * @param offsetX Specifies the x-coordinate offset.
 * @param offsetY Specifies the y-coordinate offset.
 */
void  GRRLIB_DrawTexture (const f32 xPos, const f32 yPos, const GRRLIB_texture *tex, const f32 degrees, const f32 scaleX, const f32 scaleY, const f32 offsetX, const f32 offsetY) {
	GRRLIB_DrawTexturePart(xPos, yPos, tex, &tex->part, degrees, scaleX, scaleY, offsetX, offsetY);
}

/**
 * Draw a part of a texture.
 * @param xPos Specifies the x-coordinate of the upper-left corner.
 * @param yPos Specifies the y-coordinate of the upper-left corner.
 * @param tex The texture to draw.
 * @param texPart The part of the texture to draw.
 * @param degrees Angle of rotation.
 * @param scaleX Specifies the x-coordinate scale. -1 could be used for flipping the texture horizontally.
 * @param scaleY Specifies the y-coordinate scale. -1 could be used for flipping the texture vertically.
 * @param offsetX Specifies the x-coordinate offset.
 * @param offsetY Specifies the y-coordinate offset.
 */
void  GRRLIB_DrawTexturePart (const f32 xPos, const f32 yPos, const GRRLIB_texture *tex, const GRRLIB_texturePart *texPart, const f32 degrees, const f32 scaleX, const f32 scaleY, const f32 offsetX, const f32 offsetY) {
	Mtx  m, m1, m2, mv;

	if ((tex == NULL) || (texPart == NULL))  return;

	GX_LoadTexObj(&((GRRLIB_texture *) tex)->obj, GX_TEXMAP0);
	GX_SetTevOp(GX_TEVSTAGE0, GX_MODULATE);
	GX_SetVtxDesc(GX_VA_TEX0, GX_DIRECT);

	guMtxRotAxisDeg(m1, &GRRLIB_Axis2D, degrees);
	guMtxIdentity(m2);
	guMtxTransApply(m2, m2, -offsetX, -offsetY, 0.0);
	guMtxScaleApply(m2, m2, scaleX, scaleY, 1.0);
	guMtxConcat(m1, m2, m);

	guMtxTransApply(m, m, xPos, yPos, 0.0);
	guMtxConcat(GRRLIB_View2D, m, mv);

	GX_LoadPosMtxImm(mv, GX_PNMTX0);
	GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
		GX_Position3f32(0, 0, 0);
		GX_Color1u32   (GRRLIB_Settings.color);
		GX_TexCoord2f32(texPart->x, texPart->y);

		GX_Position3f32(texPart->realWidth, 0, 0);
		GX_Color1u32   (GRRLIB_Settings.color);
		GX_TexCoord2f32(texPart->width, texPart->y);

		GX_Position3f32(texPart->realWidth, texPart->realHeight, 0);
		GX_Color1u32   (GRRLIB_Settings.color);
		GX_TexCoord2f32(texPart->width, texPart->height);

		GX_Position3f32(0, texPart->realHeight, 0);
		GX_Color1u32   (GRRLIB_Settings.color);
		GX_TexCoord2f32(texPart->x, texPart->height);
	GX_End();
	GX_LoadPosMtxImm(GRRLIB_View2D, GX_PNMTX0);

	GX_SetTevOp  (GX_TEVSTAGE0, GX_PASSCLR);
	GX_SetVtxDesc(GX_VA_TEX0,   GX_NONE);
}

/**
 * Draw a textured quad.
 * @param pos Vector array of the 4 points.
 * @param tex The texture to draw.
 */
void  GRRLIB_DrawTextureQuad (const guVector pos[4], GRRLIB_texImg *tex) {
	GXTexObj  texObj;
	Mtx       m, m1, m2, mv;
	u32       color = GRRLIB_Settings.color;

	if (tex == NULL || tex->data == NULL)  return;

	GX_InitTexObj(&texObj, tex->data, tex->w, tex->h,
				  GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, GX_FALSE);

	if (GRRLIB_Settings.antialias == false) {
		GX_InitTexObjLOD(&texObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, 0, 0, GX_ANISO_1);
	}

	GX_LoadTexObj(&texObj,      GX_TEXMAP0);
	GX_SetTevOp  (GX_TEVSTAGE0, GX_MODULATE);
	GX_SetVtxDesc(GX_VA_TEX0,   GX_DIRECT);

	guMtxIdentity  (m1);
	guMtxScaleApply(m1, m1, 1, 1, 1.0);
	guMtxRotAxisDeg(m2, &GRRLIB_Axis2D, 0);
	guMtxConcat    (m2, m1, m);
	guMtxConcat    (GRRLIB_View2D, m, mv);

	GX_LoadPosMtxImm(mv, GX_PNMTX0);
	GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
		GX_Position3f32(pos[0].x, pos[0].y, 0);
		GX_Color1u32   (color);
		GX_TexCoord2f32(0, 0);

		GX_Position3f32(pos[1].x, pos[1].y, 0);
		GX_Color1u32   (color);
		GX_TexCoord2f32(1, 0);

		GX_Position3f32(pos[2].x, pos[2].y, 0);
		GX_Color1u32   (color);
		GX_TexCoord2f32(1, 1);

		GX_Position3f32(pos[3].x, pos[3].y, 0);
		GX_Color1u32   (color);
		GX_TexCoord2f32(0, 1);
	GX_End();
	GX_LoadPosMtxImm(GRRLIB_View2D, GX_PNMTX0);

	GX_SetTevOp  (GX_TEVSTAGE0, GX_PASSCLR);
	GX_SetVtxDesc(GX_VA_TEX0,   GX_NONE);
}

/**
 * Draw a tile.
 * @param xpos Specifies the x-coordinate of the upper-left corner.
 * @param ypos Specifies the y-coordinate of the upper-left corner.
 * @param tex The texture containing the tile to draw.
 * @param degrees Angle of rotation.
 * @param scaleX Specifies the x-coordinate scale. -1 could be used for flipping the texture horizontally.
 * @param scaleY Specifies the y-coordinate scale. -1 could be used for flipping the texture vertically.
 * @param offsetX Specifies the x-coordinate offset.
 * @param offsetY Specifies the y-coordinate offset.
 * @param frame Specifies the frame to draw.
 */
void  GRRLIB_DrawTile (const f32 xpos, const f32 ypos, const GRRLIB_texImg *tex, const f32 degrees, const f32 scaleX, const f32 scaleY, const f32 offsetX, const f32 offsetY, const int frame) {
	GXTexObj  texObj;
	f32       width, height;
	Mtx       m, m1, m2, mv;
	f32       s1, s2, t1, t2;
	u32       color = GRRLIB_Settings.color;

	if (tex == NULL || tex->data == NULL)  return;

	// The 0.001f/x is the frame correction formula by spiffen
	s1 = (frame % tex->nbtilew) * tex->ofnormaltexx;
	s2 = s1 + tex->ofnormaltexx;
	t1 = (int)(frame/tex->nbtilew) * tex->ofnormaltexy;
	t2 = t1 + tex->ofnormaltexy;

	GX_InitTexObj(&texObj, tex->data,
				  tex->tilew * tex->nbtilew, tex->tileh * tex->nbtileh,
				  GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, GX_FALSE);

	if (GRRLIB_Settings.antialias == false) {
		GX_InitTexObjLOD(&texObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, 0, 0, GX_ANISO_1);
	}

	GX_LoadTexObj(&texObj,      GX_TEXMAP0);
	GX_SetTevOp  (GX_TEVSTAGE0, GX_MODULATE);
	GX_SetVtxDesc(GX_VA_TEX0,   GX_DIRECT);

	width  = tex->tilew * 0.5f - offsetX;
	height = tex->tileh * 0.5f - offsetY;

	guMtxIdentity  (m1);
	guMtxScaleApply(m1, m1, scaleX, scaleY, 1.0f);
	guMtxRotAxisDeg(m2, &GRRLIB_Axis2D, degrees);
	guMtxConcat    (m2, m1, m);

	guMtxTransApply(m, m, xpos, ypos, 0);
	guMtxConcat(GRRLIB_View2D, m, mv);

	GX_LoadPosMtxImm(mv, GX_PNMTX0);
	GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
		GX_Position3f32(-offsetX, -offsetY, 0);
		GX_Color1u32   (color);
		GX_TexCoord2f32(s1, t1);

		GX_Position3f32(width, -offsetY, 0);
		GX_Color1u32   (color);
		GX_TexCoord2f32(s2, t1);

		GX_Position3f32(width, height, 0);
		GX_Color1u32   (color);
		GX_TexCoord2f32(s2, t2);

		GX_Position3f32(-offsetX, height, 0);
		GX_Color1u32   (color);
		GX_TexCoord2f32(s1, t2);
	GX_End();
	GX_LoadPosMtxImm(GRRLIB_View2D, GX_PNMTX0);

	GX_SetTevOp  (GX_TEVSTAGE0, GX_PASSCLR);
	GX_SetVtxDesc(GX_VA_TEX0,   GX_NONE);
}

/**
 * Draw a tile in a quad.
 * @param pos Vector array of the 4 points.
 * @param tex The texture to draw.
 * @param frame Specifies the frame to draw.
 */
void  GRRLIB_DrawTileQuad (const guVector pos[4], GRRLIB_texImg *tex, const int frame) {
	GXTexObj  texObj;
	Mtx       m, m1, m2, mv;
	f32       s1, s2, t1, t2;
	u32       color = GRRLIB_Settings.color;

	if (tex == NULL || tex->data == NULL)  return;

	// The 0.001f/x is the frame correction formula by spiffen
	s1 = ((     (frame %tex->nbtilew)   ) /(f32)tex->nbtilew) +(0.001f /tex->w);
	s2 = ((     (frame %tex->nbtilew) +1) /(f32)tex->nbtilew) -(0.001f /tex->w);
	t1 = (((int)(frame /tex->nbtilew)   ) /(f32)tex->nbtileh) +(0.001f /tex->h);
	t2 = (((int)(frame /tex->nbtilew) +1) /(f32)tex->nbtileh) -(0.001f /tex->h);

	GX_InitTexObj(&texObj, tex->data,
				  tex->tilew * tex->nbtilew, tex->tileh * tex->nbtileh,
				  GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, GX_FALSE);

	if (GRRLIB_Settings.antialias == false) {
		GX_InitTexObjLOD(&texObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, 0, 0, GX_ANISO_1);
	}

	GX_LoadTexObj(&texObj,      GX_TEXMAP0);
	GX_SetTevOp  (GX_TEVSTAGE0, GX_MODULATE);
	GX_SetVtxDesc(GX_VA_TEX0,   GX_DIRECT);

	guMtxIdentity  (m1);
	guMtxScaleApply(m1, m1, 1, 1, 1.0f);
	guMtxRotAxisDeg(m2, &GRRLIB_Axis2D, 0);
	guMtxConcat    (m2, m1, m);
	guMtxConcat    (GRRLIB_View2D, m, mv);

	GX_LoadPosMtxImm(mv, GX_PNMTX0);
	GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
		GX_Position3f32(pos[0].x, pos[0].y, 0);
		GX_Color1u32   (color);
		GX_TexCoord2f32(s1, t1);

		GX_Position3f32(pos[1].x, pos[1].y, 0);
		GX_Color1u32   (color);
		GX_TexCoord2f32(s2, t1);

		GX_Position3f32(pos[2].x, pos[2].y, 0);
		GX_Color1u32   (color);
		GX_TexCoord2f32(s2, t2);

		GX_Position3f32(pos[3].x, pos[3].y, 0);
		GX_Color1u32   (color);
		GX_TexCoord2f32(s1, t2);
	GX_End();
	GX_LoadPosMtxImm(GRRLIB_View2D, GX_PNMTX0);

	GX_SetTevOp  (GX_TEVSTAGE0, GX_PASSCLR);
	GX_SetVtxDesc(GX_VA_TEX0,   GX_NONE);
}

/**
 * Call this function after drawing.
 */
void  GRRLIB_Render (void) {
	GX_DrawDone();          // Tell the GX engine we are done drawing
	GX_InvalidateTexAll();

	GRRLIB_FB ^= 1;  // Toggle framebuffer index

	GX_SetZMode      (GX_TRUE, GX_LEQUAL, GX_TRUE);
	GX_SetColorUpdate(GX_TRUE);
	GX_CopyDisp      (GRRLIB_XFB[GRRLIB_FB], GX_TRUE);

	VIDEO_SetNextFramebuffer(GRRLIB_XFB[GRRLIB_FB]);  // Select eXternal Frame Buffer
	VIDEO_Flush();                      // Flush video buffer to screen
	VIDEO_WaitVSync();                  // Wait for screen to update
	// Interlaced screens require two frames to update
	if (GRRLIB_VideoMode->viTVMode &VI_NON_INTERLACE) {
		VIDEO_WaitVSync();
	}
}
