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
 * @file GRRLIB_fb.h
 * Inline functions for drawing.
 */

/**
 * Set the background parameter when screen is cleared.
 * @param r Red component.
 * @param g Green component.
 * @param b Blue component.
 * @param a Alpha component.
 */
void GRRLIB_SetBackgroundColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
	GX_SetCopyClear((GXColor){r, g, b, a}, GX_MAX_Z24);
}

/**
 * Draw a circle.
 * @param x Specifies the x-coordinate of the circle.
 * @param y Specifies the y-coordinate of the circle.
 * @param radius The radius of the circle.
 * @param filled Set to @c true to fill the circle.
 */
static inline  void  GRRLIB_Circle (const f32 x, const f32 y, const f32 radius,
                                    const bool filled) {
	GRRLIB_Ellipse(x, y, radius, radius, filled);
}

/**
 * Draw an array of points.
 * @param v Array containing the points.
 * @param color The color of the points in RGBA format.
 * @param n Number of points in the vector array.
 */
static inline void  GRRLIB_Points (const guVector v[], const u32 color[], const long n) {
	GRRLIB_GXEngine(v, color, n, GX_POINTS);
}

/**
 * Draw a polygon.
 * @param v The vector containing the coordinates of the polygon.
 * @param color The color of the filled polygon in RGBA format.
 * @param n Number of points in the vector.
 * @param filled Set to @c true to fill the polygon.
 */
static inline void  GRRLIB_Polygon (const guVector v[], const long n, bool filled) {
	GRRLIB_GXEngine(v, NULL, n, (filled == true) ? GX_TRIANGLEFAN : GX_LINESTRIP);
}
