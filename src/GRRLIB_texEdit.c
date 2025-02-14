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

#include <malloc.h>
#include <pngu-mod.h>
#include <stdio.h>
#include <jpeglib.h>
#include <string.h>

#include <grrlib-mod.h>

/**
 * This structure contains information about the type, size, and layout of a file that containing a device-independent bitmap (DIB).
 */
typedef  struct tagBITMAPFILEHEADER {
	u16 bfType;             /**< Specifies the file type. It must be set to the signature word BM (0x4D42) to indicate bitmap. */
	u32 bfSize;             /**< Specifies the size, in bytes, of the bitmap file. */
	u16 bfReserved1;        /**< Reserved; set to zero. */
	u16 bfReserved2;        /**< Reserved; set to zero. */
	u32 bfOffBits;          /**< Specifies the offset, in bytes, from the BITMAPFILEHEADER structure to the bitmap bits. */
} BITMAPFILEHEADER;
/**
 * This structure contains information about the dimensions and color format of a device-independent bitmap (DIB).
 */
typedef  struct tagBITMAPINFOHEADER {
	u32 biSize;             /**< Specifies the size of the structure, in bytes. */
	u32 biWidth;            /**< Specifies the width of the bitmap, in pixels. */
	u32 biHeight;           /**< Specifies the height of the bitmap, in pixels. */
	u16 biPlanes;           /**< Specifies the number of planes for the target device. */
	u16 biBitCount;         /**< Specifies the number of bits per pixel. */
	u32 biCompression;      /**< Specifies the type of compression for a compressed bottom-up bitmap.*/
	u32 biSizeImage;        /**< Specifies the size, in bytes, of the image. */
	u32 biXPelsPerMeter;    /**< Specifies the horizontal resolution, in pixels per meter, of the target device for the bitmap. */
	u32 biYPelsPerMeter;    /**< Specifies the vertical resolution, in pixels per meter, of the target device for the bitmap. */
	u32 biClrUsed;          /**< Specifies the number of color indexes in the color table that are actually used by the bitmap. */
	u32 biClrImportant;     /**< Specifies the number of color indexes required for displaying the bitmap. */
} BITMAPINFOHEADER;
/**
 * The RGBQUAD structure describes a color consisting of relative intensities of
 * red, green, and blue. The bmiColors member of the BITMAPINFO structure
 * consists of an array of RGBQUAD structures.
 */
typedef  struct tagRGBQUAD {
	u8 rgbBlue;             /**< Specifies the intensity of blue in the color. */
	u8 rgbGreen;            /**< Specifies the intensity of green in the color. */
	u8 rgbRed;              /**< Specifies the intensity of red in the color. */
	u8 rgbReserved;         /**< Not used; must be set to zero. */
} RGBQUAD;

/**
 * Convert a raw BMP (RGB, no alpha) to 4x4RGBA.
 * @author DragonMinded
 * @param src Source.
 * @param dst Destination.
 * @param width Width.
 * @param height Height.
*/
static
void  RawTo4x4RGBA (const u8 *src, void *dst,
					const u32 width, const u32 height) {
	u32   block;
	u32   i;
	u8    c;
	u8    argb;

	u8    *p = (u8*)dst;

	for (block = 0; block < height; block += 4) {
		for (i = 0; i < width; i += 4) {
			// Alpha and Red
			for (c = 0; c < 4; ++c) {
				for (argb = 0; argb < 4; ++argb) {
					// Alpha pixels
					*p++ = 255;
					// Red pixels
					*p++ = src[((i + argb) + ((block + c) * width)) * 3];
				}
			}

			// Green and Blue
			for (c = 0; c < 4; ++c) {
				for (argb = 0; argb < 4; ++argb) {
					// Green pixels
					*p++ = src[(((i + argb) + ((block + c) * width)) * 3) + 1];
					// Blue pixels
					*p++ = src[(((i + argb) + ((block + c) * width)) * 3) + 2];
				}
			}
		}
	}
}

/**
 * Create an empty RGBA8 texture.
 * @param w Width of the new texture to create.
 * @param h Height of the new texture to create.
 * @return A GRRLIB_texture structure newly created.
 */
GRRLIB_texture*  GRRLIB_CreateEmptyTexture (const u32 width, const u32 height)
{
	GRRLIB_texture *my_texture = malloc(sizeof(GRRLIB_texture));

	if (my_texture != NULL) {
		my_texture->data = memalign(32, width * height * 4);

		my_texture->fmt = GX_TF_RGBA8;
		my_texture->width = width;
		my_texture->height = height;

		// Initialize the texture
		memset(my_texture->data, '\0', (width * height) << 2);

		GRRLIB_FinalizeTexture(my_texture);
	}
	return my_texture;
}

/**
 * Load a texture from a buffer.
 * @param my_img The PNG, BMP, or JPG buffer to load.
 * @return A GRRLIB_texture structure filled with image information.
 */
GRRLIB_texture*  GRRLIB_LoadTexture (const u8 *my_img) {
	if (my_img[0]==0x89 && my_img[1]=='P' && my_img[2]=='N' && my_img[3]=='G')
		return (GRRLIB_LoadTexturePNG(my_img));
	else if (my_img[0]=='B' && my_img[1]=='M')
		return (GRRLIB_LoadTextureBMP(my_img));
	else if (my_img[0]==0xFF && my_img[1]==0xD8 && my_img[2]==0xFF)
		return (GRRLIB_LoadTextureJPG(my_img));
	else
		return (NULL);
}

/**
 * Load a texture from a buffer.
 * @param my_img The JPG or TPL buffer to load.
 * @param my_size Size of the buffer to load.
 * @return A GRRLIB_texture structure filled with image information.
 */
GRRLIB_texture*  GRRLIB_LoadTextureEx (const u8 *my_img, const u32 my_size) {
	if (my_img[0]==0xFF && my_img[1]==0xD8 && my_img[2]==0xFF)
		return (GRRLIB_LoadTextureJPGEx(my_img, my_size));
	else if (my_img[0]==0x00 && my_img[1]==0x20 && my_img[2]==0xAF && my_img[3]==0x30)
		return (GRRLIB_LoadTextureTPL(my_img, my_size, 0)); // Load first texture in TPL
	else
		return (NULL);
}

/**
 * Load a texture from a buffer.
 * @param my_png the PNG buffer to load.
 * @return A GRRLIB_texture structure filled with image information.
 *         If image size is not correct, the texture will be completely transparent.
 */
GRRLIB_texture*  GRRLIB_LoadTexturePNG (const u8 *my_png) {
	int width = 0, height = 0;
	PNGUPROP imgProp;
	IMGCTX ctx;
	GRRLIB_texture *my_texture = malloc(sizeof(GRRLIB_texture));

	if (my_texture != NULL) {
		ctx = PNGU_SelectImageFromBuffer(my_png);
		PNGU_GetImageProperties(ctx, &imgProp);
		// TODO: Add support for other texture formats.
		my_texture->data = PNGU_DecodeTo4x4RGBA8(ctx, imgProp.imgWidth, imgProp.imgHeight, &width, &height, NULL);
		if (my_texture->data != NULL) {
			my_texture->fmt = GX_TF_RGBA8;
			my_texture->width = width;
			my_texture->height = height;
			if (imgProp.imgWidth != width || imgProp.imgHeight != height) {
				// PNGU has resized the texture
				memset(my_texture->data, 0, (my_texture->height * my_texture->width) << 2);
			}
			GRRLIB_FinalizeTexture(my_texture);
		}
		PNGU_ReleaseImageContext(ctx);
	}
	return my_texture;
}

/**
 * Create an array of palette.
 * @param my_bmp Bitmap buffer to parse.
 * @param Size The number of palette to add.
 * @return An array of palette. Memory must be deleted.
 */
static RGBQUAD*  GRRLIB_CreatePalette (const u8 *my_bmp, u32 Size) {
	u32 i = 0;
	RGBQUAD *Palette = calloc(Size, sizeof(RGBQUAD));
	for(u32 n=0; n<Size; n++) {
		Palette[n].rgbBlue = my_bmp[i];
		Palette[n].rgbGreen = my_bmp[i+1];
		Palette[n].rgbRed = my_bmp[i+2];
		Palette[n].rgbReserved = 0;
		i += 4;
	}
	return Palette;
}

/**
 * Load a texture from a buffer.
 * It only works for the Microsoft standard format uncompressed (1-bit, 4-bit, 8-bit, 24-bit and 32-bit).
 * @param my_bmp The bitmap buffer to load.
 * @return A GRRLIB_texture structure filled with image information.
 */
GRRLIB_texture*  GRRLIB_LoadTextureBMP (const u8 *my_bmp) {
	BITMAPFILEHEADER MyBitmapFileHeader;
	BITMAPINFOHEADER MyBitmapHeader;
	u16 pal_ref;
	u32 BufferSize;
	s32 y, x, i;
	GRRLIB_texture *my_texture = malloc(sizeof(GRRLIB_texture));

	if (my_texture != NULL) {
		// Fill file header structure
		MyBitmapFileHeader.bfType      = (my_bmp[0]  | my_bmp[1]<<8);
		MyBitmapFileHeader.bfSize      = (my_bmp[2]  | my_bmp[3]<<8  | my_bmp[4]<<16 | my_bmp[5]<<24);
		MyBitmapFileHeader.bfReserved1 = (my_bmp[6]  | my_bmp[7]<<8);
		MyBitmapFileHeader.bfReserved2 = (my_bmp[8]  | my_bmp[9]<<8);
		MyBitmapFileHeader.bfOffBits   = (my_bmp[10] | my_bmp[11]<<8 | my_bmp[12]<<16 | my_bmp[13]<<24);
		// Fill the bitmap structure
		MyBitmapHeader.biSize          = (my_bmp[14] | my_bmp[15]<<8 | my_bmp[16]<<16 | my_bmp[17]<<24);
		MyBitmapHeader.biWidth         = (my_bmp[18] | my_bmp[19]<<8 | my_bmp[20]<<16 | my_bmp[21]<<24);
		MyBitmapHeader.biHeight        = (my_bmp[22] | my_bmp[23]<<8 | my_bmp[24]<<16 | my_bmp[25]<<24);
		MyBitmapHeader.biPlanes        = (my_bmp[26] | my_bmp[27]<<8);
		MyBitmapHeader.biBitCount      = (my_bmp[28] | my_bmp[29]<<8);
		MyBitmapHeader.biCompression   = (my_bmp[30] | my_bmp[31]<<8 | my_bmp[32]<<16 | my_bmp[33]<<24);
		MyBitmapHeader.biSizeImage     = (my_bmp[34] | my_bmp[35]<<8 | my_bmp[36]<<16 | my_bmp[37]<<24);
		MyBitmapHeader.biXPelsPerMeter = (my_bmp[38] | my_bmp[39]<<8 | my_bmp[40]<<16 | my_bmp[41]<<24);
		MyBitmapHeader.biYPelsPerMeter = (my_bmp[42] | my_bmp[43]<<8 | my_bmp[44]<<16 | my_bmp[45]<<24);
		MyBitmapHeader.biClrUsed       = (my_bmp[46] | my_bmp[47]<<8 | my_bmp[48]<<16 | my_bmp[49]<<24);
		MyBitmapHeader.biClrImportant  = (my_bmp[50] | my_bmp[51]<<8 | my_bmp[52]<<16 | my_bmp[53]<<24);

		my_texture->data = memalign(32, MyBitmapHeader.biWidth * MyBitmapHeader.biHeight * 4);
		if (my_texture->data != NULL && MyBitmapFileHeader.bfType == 0x4D42) {
			RGBQUAD *Palette;
			my_texture->width = MyBitmapHeader.biWidth;
			my_texture->height = MyBitmapHeader.biHeight;
			my_texture->fmt = GX_TF_RGBA8;
			switch(MyBitmapHeader.biBitCount) {
				case 32:    // RGBA images
					i = 54;
					for(y=MyBitmapHeader.biHeight-1; y>=0; y--) {
						for(x=0; x<MyBitmapHeader.biWidth; x++) {
							GRRLIB_SetPixelToTexture(x, y, my_texture,
							                         GRRLIB_RGBA(my_bmp[i+2], my_bmp[i+1], my_bmp[i], my_bmp[i+3]));
							i += 4;
						}
					}
					break;
				case 24:    // truecolor images
					BufferSize = (MyBitmapHeader.biWidth % 4);
					i = 54;
					for(y=MyBitmapHeader.biHeight-1; y>=0; y--) {
						for(x=0; x<MyBitmapHeader.biWidth; x++) {
							GRRLIB_SetPixelToTexture(x, y, my_texture,
							                         GRRLIB_RGBA(my_bmp[i+2], my_bmp[i+1], my_bmp[i], 0xFF));
							i += 3;
						}
						i += BufferSize;   // Padding
					}
					break;
				case 8:     // 256 color images
					BufferSize = (int) MyBitmapHeader.biWidth;
					while(BufferSize % 4) {
						BufferSize++;
					}
					BufferSize -= MyBitmapHeader.biWidth;
					Palette = GRRLIB_CreatePalette(&my_bmp[54], 256);
					i = 1078; // 54 + (MyBitmapHeader.biBitCount * 4)
					for(y=MyBitmapHeader.biHeight-1; y>=0; y--) {
						for(x=0; x<MyBitmapHeader.biWidth; x++) {
							GRRLIB_SetPixelToTexture(x, y, my_texture,
							                         GRRLIB_RGBA(Palette[my_bmp[i]].rgbRed,
							                                     Palette[my_bmp[i]].rgbGreen,
							                                     Palette[my_bmp[i]].rgbBlue,
							                                     0xFF));
							i++;
						}
						i += BufferSize;   // Padding
					}
					free(Palette);
					break;
				case 4:     // 16 color images
					BufferSize = (int)((MyBitmapHeader.biWidth*4) / 8.0);
					while(8*BufferSize < MyBitmapHeader.biWidth*4) {
						BufferSize++;
					}
					while(BufferSize % 4) {
						BufferSize++;
					}
					Palette = GRRLIB_CreatePalette(&my_bmp[54], 16);
					i = 118; // 54 + (MyBitmapHeader.biBitCount * 4)
					for(y=MyBitmapHeader.biHeight-1; y>=0; y--) {
						for(x=0; x<MyBitmapHeader.biWidth; x++) {
							pal_ref = (my_bmp[i + (x / 2)] >> ((x % 2) ? 0 : 4)) & 0x0F;
							GRRLIB_SetPixelToTexture(x, y, my_texture,
							                         GRRLIB_RGBA(Palette[pal_ref].rgbRed,
							                                     Palette[pal_ref].rgbGreen,
							                                     Palette[pal_ref].rgbBlue,
							                                     0xFF));
						}
						i += BufferSize;   // Padding
					}
					free(Palette);
					break;
				case 1:     // black & white images
					BufferSize = (int)(MyBitmapHeader.biWidth / 8.0);
					while(8*BufferSize < MyBitmapHeader.biWidth) {
						BufferSize++;
					}
					while(BufferSize % 4) {
						BufferSize++;
					}
					Palette = GRRLIB_CreatePalette(&my_bmp[54], 2);
					i = 62; // 54 + (MyBitmapHeader.biBitCount * 4)
					for(y=MyBitmapHeader.biHeight-1; y>=0; y--) {
						for(x=0; x<MyBitmapHeader.biWidth; x++) {
							pal_ref = (my_bmp[i + (x / 8)] >> (-x%8+7)) & 0x01;
							GRRLIB_SetPixelToTexture(x, y, my_texture,
							                         GRRLIB_RGBA(Palette[pal_ref].rgbRed,
								                                 Palette[pal_ref].rgbGreen,
								                                 Palette[pal_ref].rgbBlue,
								                                 0xFF));
						}
						i += BufferSize;   // Padding
					}
					free(Palette);
					break;
				default:
					GRRLIB_ClearTexture(my_texture);
			}
			GRRLIB_FinalizeTexture(my_texture);
		}
	}
	return my_texture;
}

/**
 * Load a texture from a buffer.
 * Take care to have the JPG finish with 0xFF 0xD9!
 * @param my_jpg The JPEG buffer to load.
 * @return A GRRLIB_texture structure filled with image information.
 */
GRRLIB_texture*  GRRLIB_LoadTextureJPG (const u8 *my_jpg) {
	int n = 0;

	if ((my_jpg[0]==0xFF) && (my_jpg[1]==0xD8) && (my_jpg[2]==0xFF)) {
		while(true) {
			if ((my_jpg[n]==0xFF) && (my_jpg[n+1]==0xD9))
				break;
			n++;
		}
		n+=2;
	}

	return GRRLIB_LoadTextureJPGEx(my_jpg, n);
}

/**
 * Load a texture from a buffer.
 * @author DrTwox
 * @param my_jpg The JPEG buffer to load.
 * @param my_size Size of the JPEG buffer to load.
 * @return A GRRLIB_texture structure filled with texture information.
 */
GRRLIB_texture*  GRRLIB_LoadTextureJPGEx (const u8 *my_jpg, const u32 my_size) {
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;
	GRRLIB_texture *my_texture = malloc(sizeof(GRRLIB_texture));

	if (my_texture == NULL) {
		return NULL;
	}

	jpeg_create_decompress(&cinfo);
	cinfo.err = jpeg_std_error(&jerr);
	cinfo.progress = NULL;
	jpeg_mem_src(&cinfo, (unsigned char *)my_jpg, my_size);
	jpeg_read_header(&cinfo, TRUE);
	if (cinfo.jpeg_color_space == JCS_GRAYSCALE) {
		cinfo.out_color_space = JCS_RGB;
	}
	jpeg_start_decompress(&cinfo);
	unsigned char *tempBuffer = malloc(cinfo.output_width * cinfo.output_height * cinfo.output_components);
	JSAMPROW row_pointer[1];
	row_pointer[0] = malloc(cinfo.output_width * cinfo.output_components);
	size_t location = 0;
	while (cinfo.output_scanline < cinfo.output_height) {
		jpeg_read_scanlines(&cinfo, row_pointer, 1);
		for (unsigned int i = 0; i < cinfo.image_width * cinfo.output_components; i++) {
			/* Put the decoded scanline into the tempBuffer */
			tempBuffer[ location++ ] = row_pointer[0][i];
		}
	}

	/* Create a buffer to hold the final texture */
	my_texture->data = memalign(32, cinfo.output_width * cinfo.output_height * 4);
	RawTo4x4RGBA(tempBuffer, my_texture->data, cinfo.output_width, cinfo.output_height);

	/* Done - Do cleanup and release allocated memory */
	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);
	free(row_pointer[0]);
	free(tempBuffer);

	my_texture->fmt = GX_TF_RGBA8;
	my_texture->width = cinfo.output_width;
	my_texture->height = cinfo.output_height;

	GRRLIB_FinalizeTexture(my_texture);

	return my_texture;
}

/**
 * Load a texture from a buffer.
 * @param my_tpl The TPL buffer to load.
 * @param my_size Size of the TPL buffer to load.
 * @param my_id Texture ID to load.
 * @return A GRRLIB_texture structure filled with texture information.
 */
GRRLIB_texture*  GRRLIB_LoadTextureTPL (const u8 *my_tpl, const u32 my_size, const s32 my_id) {
	void *tplData = memalign(32, my_size);
	TPLFile *tdf = malloc(sizeof(TPLFile));
	u16 w, h;
	GRRLIB_texture *my_texture = malloc(sizeof(GRRLIB_texture));

	memcpy(tplData, (const void *) my_tpl, my_size);

	if (TPL_OpenTPLFromMemory(tdf, tplData, my_size) < 0) {
		return NULL;
	}

	TPL_GetTextureInfo(tdf, my_id, &my_texture->fmt, &w, &h);
	my_texture->width = (u32) w;
	my_texture->height = (u32) h;

	TPL_GetTexture(tdf, my_id, &my_texture->obj); // No need to finalize texture

	GRRLIB_SetTexturePart(my_texture);

	return my_texture;
}

/**
 * Define coordinates of a texture and store them for later use.
 * @param x X coordinate of the texture.
 * @param y Y coordinate of the texture.
 * @param width Width of the part of the texture.
 * @param height Height of the part of the texture.
 * @param texture Texture to use as the reference width and height.
 */
GRRLIB_texturePart*  GRRLIB_CreateTexturePart (const f32 x, const f32 y, const f32 width, const f32 height, const GRRLIB_texture *texture) {
	return GRRLIB_CreateTexturePartEx(x, y, width, height, texture->width, texture->height);
}

/**
 * Define texture coordinates and store them for later use.
 * @param x X coordinate of the texture.
 * @param y Y coordinate of the texture.
 * @param width Width of the part of the texture.
 * @param height Height of the part of the texture.
 * @param textureWidth Width of the texture.
 * @param textureHeight Height of the texture.
 */
GRRLIB_texturePart*  GRRLIB_CreateTexturePartEx (const f32 x, const f32 y, const f32 width, const f32 height, const u32 textureWidth, const u32 textureHeight) {
	GRRLIB_texturePart *texPart = malloc(sizeof(GRRLIB_texturePart));

	// The 0.001f/x is the frame correction formula by spiffen
	texPart->x = (x /textureWidth) +(0.001f /textureWidth);
	texPart->y = (y /textureHeight) +(0.001f /textureHeight);
	texPart->width = ((x + width)/textureWidth) -(0.001f /textureWidth);
	texPart->height = ((y + height)/textureHeight) -(0.001f /textureHeight);

	texPart->realX = x;
	texPart->realY = y;
	texPart->realWidth = width;
	texPart->realHeight = height;

	texPart->textureWidth = textureWidth;
	texPart->textureHeight = textureHeight;

	return texPart;
}
