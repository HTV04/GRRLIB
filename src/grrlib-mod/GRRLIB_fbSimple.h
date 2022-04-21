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
 * @file GRRLIB_fbSimple.h
 * Inline functions for primitive point and line drawing.
 */

/**
 * Fill screen with a specific color.
 * @param color The color to use to fill the screen.
 */
INLINE
void  GRRLIB_FillScreen (const u32 color) {
	f32 x = -40.0f;
	f32 y = -40.0f;
	f32 x2 = x + rmode->fbWidth + 80.0f;
	f32 y2 = y + rmode->xfbHeight + 80.0f;

	GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
		GX_Position3f32(x, y, 0.0f);
		GX_Color1u32(color);
		GX_Position3f32(x2, y, 0.0f);
		GX_Color1u32(color);
		GX_Position3f32(x2, y2, 0.0f);
		GX_Color1u32(color);
		GX_Position3f32(x, y2, 0.0f);
		GX_Color1u32(color);
	GX_End();
}
