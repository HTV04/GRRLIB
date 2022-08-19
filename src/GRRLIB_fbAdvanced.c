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
 * Draw an ellipse.
 * @author Dark_Link
 * @param x Specifies the x-coordinate of the ellipse.
 * @param y Specifies the y-coordinate of the ellipse.
 * @param radiusX The X radius of the ellipse.
 * @param radiusY The Y radius of the ellipse.
 * @param filled Set to @c true to fill the ellipse.
 */
void  GRRLIB_Ellipse (const f32 x, const f32 y,
                      const f32 radiusX, const f32 radiusY,
					  const bool filled) {
	guVector v[36];
	u32 ncolor[36];
	const f32 G_DTOR = M_DTOR * 10;

	for (u32 a = 0; a < 36; a++) {
    	const f32 ra = a * G_DTOR;

		v[a].x = cos(ra) * radiusX + x;
		v[a].y = sin(ra) * radiusY + y;
		v[a].z = 0.0f;
		ncolor[a] = GRRLIB_Settings.color;
	}

	if (filled == false) {
		GRRLIB_GXEngine(v, ncolor, 36, GX_LINESTRIP);
	}
	else {
		GRRLIB_GXEngine(v, ncolor, 36, GX_TRIANGLEFAN);
	}
}
