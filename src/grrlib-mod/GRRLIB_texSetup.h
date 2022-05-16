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
 * @file GRRLIB_texSetup.h
 * Inline functions for the basic manipulation of textures.
 */

#include <malloc.h>
#include <string.h>

/**
 * Clear a texture to transparent black.
 * @param tex Texture to clear.
 */
INLINE
void  GRRLIB_ClearTexture(GRRLIB_texture* tex) {
	memset(tex->data, 0, (tex->h * tex->w) << 2);
}


/**
 * Write texture data to main memory and create a GXTexObj.
 * For performance, the CPU holds a data cache where modifications are stored before they get written down to main memory.
 * The texture should not be modified after this function is called.
 * @param tex The texture to finalize.
 */
INLINE
void  GRRLIB_FinalizeTexture(GRRLIB_texture *texture) {
	// TODO: Add support for other texture formats.
	DCFlushRange(texture->data, texture->w * texture->h * 4);
	GX_InitTexObj(&texture->obj, texture->data, texture->w, texture->h,
	              texture->fmt, GX_CLAMP, GX_CLAMP, GX_FALSE);
}

/**
 * Free memory allocated for a texture.
 * If \a tex is a null pointer, the function does nothing.
 * @note This function does not change the value of \a tex itself, hence it still points to the same (now invalid) location.
 * @param texture A GRRLIB_texture structure.
 */
INLINE
void  GRRLIB_FreeTexture(GRRLIB_texture *tex) {
	if(tex != NULL) {
		if (tex->data != NULL) {
			free(tex->data);
		}
		free(tex);
	}
}
