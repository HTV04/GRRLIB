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
 * Do not include GRRLIB__inline.h directly, include only GRRLIB.h.
 */
/**
 * @addtogroup AllFunc
 * @{
 */

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
INLINE  void  GRRLIB_ClipReset   (void);
INLINE  void  GRRLIB_ClipDrawing (const int x, const int y,
                                  const int width, const int height);

//------------------------------------------------------------------------------
// GRRLIB_collision.h - Collision detection
INLINE  bool  GRRLIB_PtInRect   (const int hotx,   const int hoty,
                                 const int hotw,   const int hoth,
                                 const int wpadx,  const int wpady);

INLINE  bool  GRRLIB_RectInRect (const int rect1x, const int rect1y,
                                 const int rect1w, const int rect1h,
                                 const int rect2x, const int rect2y,
                                 const int rect2w, const int rect2h);

INLINE  bool  GRRLIB_RectOnRect (const int rect1x, const int rect1y,
                                 const int rect1w, const int rect1h,
                                 const int rect2x, const int rect2y,
                                 const int rect2w, const int rect2h);

//------------------------------------------------------------------------------
// GRRLIB_fbComplex.h -
INLINE  void  GRRLIB_NPlot       (const guVector v[], const u32 color[],
                                  const long n);
INLINE  void  GRRLIB_NGone       (const guVector v[], const u32 color[],
                                  const long n);
INLINE  void  GRRLIB_NGoneFilled (const guVector v[], const u32 color[],
                                  const long n);

//------------------------------------------------------------------------------
// GRRLIB_fbGX.h -
INLINE  void  GRRLIB_GXEngine (const guVector v[], const u32 color[],
                               const long n,       const u8 fmt);

//------------------------------------------------------------------------------
// GRRLIB_fbSimple.h -
INLINE  void  GRRLIB_FillScreen (const u32 color);

//------------------------------------------------------------------------------
// GRRLIB_pixel.h - Pixel manipulation
INLINE  u32   GRRLIB_GetPixelFromtexImg (const int x, const int y,
                                         const GRRLIB_texImg *tex);

INLINE  void  GRRLIB_SetPixelTotexImg   (const int x, const int y,
                                         GRRLIB_texImg *tex, const u32 color);

INLINE u32 GRRLIB_GetPixelFromFB (int x, int y);
INLINE void GRRLIB_SetPixelToFB (int x, int y, u32 pokeColor);

//------------------------------------------------------------------------------
// GRRLIB_settings.h - Rendering functions
INLINE  void              GRRLIB_SetBlend        (const GRRLIB_blendMode blendmode);
INLINE  GRRLIB_blendMode  GRRLIB_GetBlend        (void);
INLINE  void              GRRLIB_SetAntiAliasing (const bool aa);
INLINE  bool              GRRLIB_GetAntiAliasing (void);

//------------------------------------------------------------------------------
// GRRLIB_texSetup.h - Create and setup textures
INLINE  void            GRRLIB_ClearTex           (GRRLIB_texImg* tex);
INLINE  void            GRRLIB_FlushTex           (GRRLIB_texImg *tex);
INLINE  void            GRRLIB_FreeTexture        (GRRLIB_texImg *tex);

//==============================================================================
// Definitions of inlined functions
//==============================================================================
#include <grrlib-mod/GRRLIB_clipping.h>   // Clipping control
#include <grrlib-mod/GRRLIB_collision.h>  // Collision detection
#include <grrlib-mod/GRRLIB_fbComplex.h>  // Render to framebuffer: Complex primitives
#include <grrlib-mod/GRRLIB_fbGX.h>       // Render to framebuffer: Simple GX wrapper
#include <grrlib-mod/GRRLIB_fbSimple.h>   // Render to framebuffer: Simple primitives
#include <grrlib-mod/GRRLIB_pixel.h>      // Pixel manipulation
#include <grrlib-mod/GRRLIB_settings.h>   // GRRLIB Settings
#include <grrlib-mod/GRRLIB_texSetup.h>   // Setup for textures

#endif // __GRRLIB_FNINLINE_H__
/** @} */ // end of group
