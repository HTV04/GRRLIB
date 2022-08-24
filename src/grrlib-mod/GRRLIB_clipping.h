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
 * @file GRRLIB_clipping.h
 * Inline functions to control clipping.
 */

/**
 * Reset the clipping to normal.
 */
static inline void  GRRLIB_ResetScissor (void) {
    GX_SetScissor( 0, 0, GRRLIB_VideoMode->fbWidth, GRRLIB_VideoMode->efbHeight );
}

/**
 * Clip the drawing area to an rectangle.
 * @param x The x-coordinate of the rectangle.
 * @param y The y-coordinate of the rectangle.
 * @param width The width of the rectangle.
 * @param height The height of the rectangle.
 */
static inline void  GRRLIB_SetScissor (const unsigned int x, const unsigned int y,
                                       const unsigned int width, const unsigned int height) {
    GX_SetScissor( x, y, width, height );
}

/**
 * Get the clip rectangle coordinates.
 * @param x The x-coordinate of the rectangle.
 * @param y The y-coordinate of the rectangle.
 * @param width The width of the rectangle.
 * @param height The height of the rectangle.
 */
static inline void  GRRLIB_GetScissor (unsigned int *x, unsigned int *y,
                                       unsigned int *width, unsigned int *height) {
    GX_GetScissor( x, y, width, height );
}
