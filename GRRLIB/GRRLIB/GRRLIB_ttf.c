/*------------------------------------------------------------------------------
Copyright (c) 2009-2020 The GRRLIB Team

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

#include "grrlib/GRRLIB_private.h"
#include <grrlib.h>
#include <wchar.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_BITMAP_H
#include <math.h>

extern Mtx GXmodelView2D;

static FT_Library ftLibrary; /**< A handle to a FreeType library instance. */
static guVector axis = (guVector){0, 0, 1};

// Static function prototypes
static void DrawBitmap(FT_Bitmap *bitmap, const f32 offset, const f32 top, const f32 degrees, const f32 scaleX, const f32 scaleY, const u8 cR, const u8 cG, const u8 cB);


/**
 * Initialize FreeType library.
 * @return int 0=OK; -1=Failed
 */
int GRRLIB_InitTTF () {
    if (FT_Init_FreeType(&ftLibrary) != 0) {
        return -1;
    }
    return 0;
}

/**
 * Call this when your done with FreeType.
 */
void GRRLIB_ExitTTF (void) {
    FT_Done_FreeType(ftLibrary);
}

/**
 * Load a TTF from a buffer.
 * @param file_base Buffer with TTF data. You must not deallocate the memory before calling GRRLIB_FreeTTF.
 * @param file_size Size of the TTF buffer.
 * @return A handle to a given TTF font object or NULL if it fails to load the font.
 * @see GRRLIB_FreeTTF
 */
GRRLIB_ttfFont* GRRLIB_LoadTTF (const u8* file_base, s32 file_size) {
    FT_Face Face;
    if (FT_New_Memory_Face(ftLibrary, file_base, file_size, 0, &Face) != 0) {
        return NULL;
    }
    GRRLIB_ttfFont* myFont = (GRRLIB_ttfFont*)malloc(sizeof(GRRLIB_ttfFont));
    myFont->kerning = FT_HAS_KERNING(Face);
/*
    if (FT_Set_Pixel_Sizes(Face, 0, fontSize) != 0) {
        FT_Set_Pixel_Sizes(Face, 0, 12);
    }
*/
    myFont->face = Face;
    return myFont;
}

/**
 * Free memory allocated by TTF fonts.
 * If \a myFont is a null pointer, the function does nothing.
 * @note This function does not change the value of \a myFont itself, hence it still points to the same (now invalid) location.
 * @param myFont A TTF.
 */
void  GRRLIB_FreeTTF (GRRLIB_ttfFont *myFont) {
    if (myFont != NULL) {
        FT_Done_Face(myFont->face);
        free(myFont);
    }
}

/**
 * Print function for TTF font.
 * @param x Specifies the x-coordinate of the upper-left corner of the text.
 * @param y Specifies the y-coordinate of the upper-left corner of the text.
 * @param myFont A TTF.
 * @param string Text to draw.
 * @param fontSize Size of the font.
 * @param degrees Angle of rotation.
 * @param scaleX Specifies the x-coordinate scale. -1 could be used for flipping the texture horizontally.
 * @param scaleY Specifies the y-coordinate scale. -1 could be used for flipping the texture vertically.
 * @param color Text color in RGBA format.
 */
void GRRLIB_PrintfTTF(const f32 x, const f32 y, GRRLIB_ttfFont *myFont, const char *string, unsigned int fontSize, const f32 degrees, const f32 scaleX, const f32 scaleY, const u32 color) {
    if (myFont == NULL || string == NULL) {
        return;
    }

    size_t length = strlen(string) + 1;
    wchar_t *utf32 = (wchar_t*)malloc(length * sizeof(wchar_t));
    if (utf32 != NULL) {
        length = mbstowcs(utf32, string, length);
        if (length > 0) {
            utf32[length] = L'\0';
            GRRLIB_PrintfTTFW(x, y, myFont, utf32, fontSize, degrees, scaleX, scaleY, color);
        }
        free(utf32);
    }
}

/**
 * Print function for TTF font.
 * @author wplaat and DrTwox
 * @param x Specifies the x-coordinate of the upper-left corner of the text.
 * @param y Specifies the y-coordinate of the upper-left corner of the text.
 * @param myFont A TTF.
 * @param utf32 Text to draw.
 * @param fontSize Size of the font.
 * @param degrees Angle of rotation.
 * @param scaleX Specifies the x-coordinate scale. -1 could be used for flipping the texture horizontally.
 * @param scaleY Specifies the y-coordinate scale. -1 could be used for flipping the texture vertically.
 * @param color Text color in RGBA format.
 */
void GRRLIB_PrintfTTFW(const f32 x, const f32 y, GRRLIB_ttfFont *myFont, const wchar_t *utf32, unsigned int fontSize, const f32 degrees, const f32 scaleX, const f32 scaleY, const u32 color) {
    if (myFont == NULL || utf32 == NULL) {
        return;
    }

    FT_Face Face = (FT_Face)myFont->face;
    f32 penX = 0;
    f32 penY = fontSize;
    FT_GlyphSlot slot = Face->glyph;
    FT_UInt glyphIndex;
    FT_UInt previousGlyph = 0;
    u8 cR = R(color), cG = G(color), cB = B(color);

    if (FT_Set_Pixel_Sizes(Face, 0, fontSize) != 0) {
        FT_Set_Pixel_Sizes(Face, 0, 12);
    }

    /* Loop over each character, until the
     * end of the string is reached, or until the pixel width is too wide */
    while(*utf32) {
        glyphIndex = FT_Get_Char_Index(myFont->face, *utf32++);

        if (myFont->kerning && previousGlyph && glyphIndex) {
            FT_Vector delta;
            FT_Get_Kerning(myFont->face, previousGlyph, glyphIndex, FT_KERNING_DEFAULT, &delta);
            penX += (f32) (delta.x >> 6) * scaleX;
        }
        if (FT_Load_Glyph(myFont->face, glyphIndex, FT_LOAD_RENDER) != 0) {
            continue;
        }

        DrawBitmap(&slot->bitmap,
                   penX + (f32) slot->bitmap_left + x,
                   penY - (f32) slot->bitmap_top + y,
                   degrees,
                   scaleX, scaleY,
                   cR, cG, cB);
        penX += (f32) (slot->advance.x >> 6) * scaleX;
        previousGlyph = glyphIndex;
    }
}

/**
 * Draw a character on the screen.
 * @param bitmap Bitmap to draw.
 * @param offset x-coordinate offset.
 * @param top y-coordinate.
 * @param degrees Angle of rotation.
 * @param scaleX Specifies the x-coordinate scale. -1 could be used for flipping the texture horizontally.
 * @param scaleY Specifies the y-coordinate scale. -1 could be used for flipping the texture vertically.
 * @param cR Red component of the colour.
 * @param cG Green component of the colour.
 * @param cB Blue component of the colour.
 */
static void DrawBitmap(FT_Bitmap *bitmap, const f32 offset, const f32 top, const f32 degrees, const f32 scaleX, const f32 scaleY, const u8 cR, const u8 cG, const u8 cB) {
    GXTexObj texObj;
    u16 width, height;
    u32 color = RGBA(cR, cG, cB, 255);
    Mtx m, m1, m2, mv;
    /*
    f32 i, j;
    FT_Int p, q;
    FT_Int x_max = offset + bitmap->width;
    FT_Int y_max = top + bitmap->rows;
    */

    FT_Bitmap tempBitmap;
    FT_Bitmap_New(&tempBitmap);
    FT_Bitmap_Convert(ftLibrary, bitmap, &tempBitmap, 1);

    DCFlushRange(tempBitmap.buffer, tempBitmap.width * tempBitmap.rows * 4);

    GX_InitTexObj(&texObj, tempBitmap.buffer, tempBitmap.width, tempBitmap.rows,
                  GX_TF_I8, GX_CLAMP, GX_CLAMP, GX_FALSE);

    if (GRRLIB_Settings.antialias == false) {
        GX_InitTexObjLOD(&texObj, GX_NEAR, GX_NEAR,
                         0.0f, 0.0f, 0.0f, 0, 0, GX_ANISO_1);
        GX_SetCopyFilter(GX_FALSE, rmode->sample_pattern, GX_FALSE, rmode->vfilter);
    }
    else {
        GX_SetCopyFilter(rmode->aa, rmode->sample_pattern, GX_TRUE, rmode->vfilter);
    }

    GX_LoadTexObj(&texObj,      GX_TEXMAP0);
    GX_SetTevOp  (GX_TEVSTAGE0, GX_MODULATE);
    GX_SetVtxDesc(GX_VA_TEX0,   GX_DIRECT);

    guMtxIdentity(m1);
    guMtxScaleApply(m1, m1, scaleX, scaleY, 1.0);
    guMtxRotAxisDeg(m2, &axis, degrees);
    guMtxConcat(m2, m1, m);
    guMtxConcat(GXmodelView2D, m, mv);

    width  = (f32) tempBitmap.width * 0.5;
    height = (f32) tempBitmap.rows * 0.5;

    guMtxTransApply(m, m,
        offset +width,
        top +height,
        0);
    guMtxConcat(GXmodelView2D, m, mv);

    GX_LoadPosMtxImm(mv, GX_PNMTX0);
    GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
        GX_Position3f32(-width, -height, 0);
        GX_Color1u32   (color);
        GX_TexCoord2f32(0, 0);

        GX_Position3f32(width, -height, 0);
        GX_Color1u32   (color);
        GX_TexCoord2f32(1, 0);

        GX_Position3f32(width, height, 0);
        GX_Color1u32   (color);
        GX_TexCoord2f32(1, 1);

        GX_Position3f32(-width, height, 0);
        GX_Color1u32   (color);
        GX_TexCoord2f32(0, 1);
    GX_End();
    GX_LoadPosMtxImm(GXmodelView2D, GX_PNMTX0);

    GX_SetTevOp  (GX_TEVSTAGE0, GX_PASSCLR);
    GX_SetVtxDesc(GX_VA_TEX0,   GX_NONE);

    FT_Bitmap_Done(ftLibrary, &tempBitmap);

    /*
    GX_LoadPosMtxImm(mv, GX_PNMTX0);
    for ( i = offset, p = 0; i < x_max; i++, p++ ) {
        for ( j = top, q = 0; j < y_max; j++, q++ ) {
            GX_Begin(GX_POINTS, GX_VTXFMT0, 1);
                GX_Position3f32(i, j, 0);
                GX_Color4u8(cR, cG, cB,
                            bitmap->buffer[ q * bitmap->width + p ]);
            GX_End();
        }
    }
    GX_LoadPosMtxImm(GXmodelView2D, GX_PNMTX0);
    */
}

/**
 * Get the width of a text in pixel.
 * @param myFont A TTF.
 * @param string The text to check.
 * @param fontSize The size of the font.
 * @return The width of a text in pixel.
 */
u32 GRRLIB_WidthTTF(GRRLIB_ttfFont *myFont, const char *string, unsigned int fontSize) {
    if (myFont == NULL || string == NULL) {
        return 0;
    }
    u32 penX;
    size_t length = strlen(string) + 1;
    wchar_t *utf32 = (wchar_t*)malloc(length * sizeof(wchar_t));
    length = mbstowcs(utf32, string, length);
    utf32[length] = L'\0';

    penX = GRRLIB_WidthTTFW(myFont, utf32, fontSize);

    free(utf32);

    return penX;
}

/**
 * Get the width of a text in pixel.
 * @param myFont A TTF.
 * @param utf32 The text to check.
 * @param fontSize The size of the font.
 * @return The width of a text in pixel.
 */
u32 GRRLIB_WidthTTFW(GRRLIB_ttfFont *myFont, const wchar_t *utf32, unsigned int fontSize) {
    if (myFont == NULL || utf32 == NULL) {
        return 0;
    }

    FT_Face Face = (FT_Face)myFont->face;
    u32 penX = 0;
    FT_UInt glyphIndex;
    FT_UInt previousGlyph = 0;

    if (FT_Set_Pixel_Sizes(myFont->face, 0, fontSize) != 0) {
         FT_Set_Pixel_Sizes(myFont->face, 0, 12);
    }

    while(*utf32) {
        glyphIndex = FT_Get_Char_Index(myFont->face, *utf32++);

        if (myFont->kerning && previousGlyph && glyphIndex) {
            FT_Vector delta;
            FT_Get_Kerning(Face, previousGlyph, glyphIndex, FT_KERNING_DEFAULT, &delta);
            penX += delta.x >> 6;
        }
        if (FT_Load_Glyph(Face, glyphIndex, FT_LOAD_RENDER) != 0) {
            continue;
        }

        penX += Face->glyph->advance.x >> 6;
        previousGlyph = glyphIndex;
    }

    return penX;
}
