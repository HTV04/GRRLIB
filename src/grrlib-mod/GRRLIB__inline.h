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

/**
 * @file GRRLIB__inline.h
 * GRRLIB inline function prototypes.
 * Do not include GRRLIB__inline.h directly, include only grrlib-mod.h.
 */
/**
 * @addtogroup AllFunc
 * @{
 */

#pragma once

#ifndef __GRRLIB_H__
#  error Do not include GRRLIB__inline.h directly, include only GRRLIB.h
#endif

#ifndef __GRRLIB_FNINLINE_H__
#define __GRRLIB_FNINLINE_H__

//==============================================================================
// Prototypes for inlined functions
//==============================================================================

//------------------------------------------------------------------------------
// GRRLIB_clipping.h - Clipping control
static inline void  GRRLIB_ResetScissor  (void);
static inline void  GRRLIB_SetScissor  (const unsigned int x, const unsigned int y,
                                        const unsigned int width, const unsigned int height);
static inline void  GRRLIB_GetScissor  (unsigned int *x, unsigned int *y,
                                        unsigned int *width, unsigned int *height);

//------------------------------------------------------------------------------
// GRRLIB_collision.h - Collision detection
static inline bool  GRRLIB_PtInRect   (const int hotx,   const int hoty,
                                         const int hotw,   const int hoth,
                                         const int wpadx,  const int wpady);

static inline bool  GRRLIB_RectInRect (const int rect1x, const int rect1y,
                                         const int rect1w, const int rect1h,
                                         const int rect2x, const int rect2y,
                                         const int rect2w, const int rect2h);

static inline bool  GRRLIB_RectOnRect (const int rect1x, const int rect1y,
                                         const int rect1w, const int rect1h,
                                         const int rect2x, const int rect2y,
                                         const int rect2w, const int rect2h);

//------------------------------------------------------------------------------
// GRRLIB_fb.h -
static inline void  GRRLIB_SetBackgroundColor  (unsigned char r, unsigned char g, unsigned char b, unsigned char a);
static inline void  GRRLIB_Circle  (const f32 x,      const f32 y,
                                    const f32 radius, const bool filled);
static inline void  GRRLIB_Points  (const guVector v[], const u32 color[],
                                   const long n);
static inline void  GRRLIB_Polygon  (const guVector v[], const long n,
                                     bool filled);

//------------------------------------------------------------------------------
// GRRLIB_pixel.h - Pixel manipulation
static inline u32   GRRLIB_GetPixelFromTexture (const int x, const int y,
                                                  const GRRLIB_texture *tex);

static inline void  GRRLIB_SetPixelToTexture   (const int x, const int y,
                                                  GRRLIB_texture *tex, const u32 color);

static inline u32 GRRLIB_GetPixelFromFB (int x, int y);
static inline void GRRLIB_SetPixelToFB  (int x, int y, u32 pokeColor);

//------------------------------------------------------------------------------
// GRRLIB_settings.h - Rendering functions
static inline void              GRRLIB_SetColor        (const u32 color);
static inline u32               GRRLIB_GetColor        (void);
static inline void              GRRLIB_SetPointSize    (const u8 pointSize);
static inline u8                GRRLIB_GetPointSize    (void);
static inline void              GRRLIB_SetLineWidth    (const u8 lineWidth);
static inline u8                GRRLIB_GetLineWidth    (void);
static inline void              GRRLIB_SetBlend        (const GRRLIB_blendMode blendmode);
static inline GRRLIB_blendMode  GRRLIB_GetBlend        (void);
static inline void              GRRLIB_SetAntiAliasing (const bool aa);
static inline bool              GRRLIB_GetAntiAliasing (void);
static inline void              GRRLIB_SetDeflicker    (const bool deflicker);
static inline bool              GRRLIB_GetDeflicker    (void);

//------------------------------------------------------------------------------
// GRRLIB_texSetup.h - Create and setup textures and texture coordinates
static inline void            GRRLIB_ClearTexture    (GRRLIB_texture *texture);
static inline void            GRRLIB_SetTexturePart  (GRRLIB_texture *texture);
static inline void            GRRLIB_FinalizeTexture (GRRLIB_texture *texture);
static inline void            GRRLIB_FreeTexture     (GRRLIB_texture *texture);
static inline void            GRRLIB_FreeTexturePart (GRRLIB_texturePart *texturePart);

//==============================================================================
// Definitions of inlined functions
//==============================================================================
#include <grrlib-mod/GRRLIB_clipping.h>   // Clipping control
#include <grrlib-mod/GRRLIB_collision.h>  // Collision detection
#include <grrlib-mod/GRRLIB_fb.h>         // Render to framebuffer
#include <grrlib-mod/GRRLIB_pixel.h>      // Pixel manipulation
#include <grrlib-mod/GRRLIB_settings.h>   // GRRLIB Settings
#include <grrlib-mod/GRRLIB_texSetup.h>   // Setup for textures

#endif // __GRRLIB_FNstatic  inline_H__
/** @} */ // end of group
