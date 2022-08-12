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
 * @param texture Texture to clear.
 */
INLINE
void  GRRLIB_ClearTexture(GRRLIB_texture *texture) {
	memset(texture->data, 0, (texture->height * texture->width) << 2);
}

/**
 * Initialize a texture's internal texture part.
 * @param texture Texture to clear.
 */
INLINE
void  GRRLIB_SetTexturePart(GRRLIB_texture *texture) {
	texture->part.x = 0;
	texture->part.y = 0;
	texture->part.width = 1;
	texture->part.height = 1;

	texture->part.realX = 0;
	texture->part.realY = 0;
	texture->part.realWidth = texture->width;
	texture->part.realHeight = texture->height;

	texture->part.textureWidth = texture->width;
	texture->part.textureHeight = texture->height;
}

/**
 * Write texture data to main memory and create a GXTexObj.
 * For performance, the CPU holds a data cache where modifications are stored before they get written down to main memory.
 * The texture should not be modified after this function is called.
 * @param texture The texture to finalize.
 */
INLINE
void  GRRLIB_FinalizeTexture(GRRLIB_texture *texture) {
	// TODO: Add support for other texture formats.
	DCFlushRange(texture->data, texture->width * texture->height * 4);
	GX_InitTexObj(&texture->obj, texture->data, texture->width, texture->height,
	              texture->fmt, GX_CLAMP, GX_CLAMP, GX_FALSE);

	GRRLIB_SetTexturePart(texture);
}

/**
 * Free memory allocated for a texture.
 * If \a texture is a null pointer, the function does nothing.
 * @note This function does not change the value of \a texture itself, hence it still points to the same (now invalid) location.
 * @param texture A GRRLIB_texture structure.
 */
INLINE
void  GRRLIB_FreeTexture(GRRLIB_texture *texture) {
	if(texture != NULL) {
		if (texture->data != NULL) {
			free(texture->data);
		}
		free(texture);
	}
}

/**
 * Free memory allocated for a texture part.
 * If \a texturePart is a null pointer, the function does nothing.
 * @note This function does not change the value of \a texturePart itself, hence it still points to the same (now invalid) location.
 * @param texturePart A GRRLIB_texturePart structure.
 */
INLINE
void  GRRLIB_FreeTexturePart(GRRLIB_texturePart *texturePart) {
	if(texturePart != NULL) {
		free(texturePart);
	}
}
