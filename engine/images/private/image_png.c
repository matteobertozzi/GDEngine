#include <GDEngine/Config.h>

#if defined(GD_ENGINE_PNG_SUPPORT)

#include <png.h>

#include "imagereader.h"
#include "macros.h"
#include "alloc.h"

/**
 * Returns true if specified file is PNG.
 */
GDBool __isPngImage (FILE *fh) {
    unsigned char sig[8];

    fseek(fh, 0, SEEK_SET);

    if (fread(sig, sizeof(unsigned char), 8, fh) != 8)
        return(GD_FALSE);

    return(png_check_sig(sig, 8));
}

/**
 * Returns True and fill Image Data Structure with specified file.
 */
GDImage *__pngImageRead (GDImage *image, FILE *fh) {
    png_uint_32 width, height;
    png_uint_32 i, rowBytes;
    png_bytepp rowPointers;
    int bitDepth, color;
    GDByte *blob;   
    png_structp png;
    png_infop info;

    /* Create PNG Read Struct */
    png = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
    gdReturnValueIfNull(png, NULL);

    /* Create Info Struct */
    if (!(info = png_create_info_struct(png))) {
        png_destroy_read_struct(&png, NULL, NULL);
        return(NULL);
    }

    setjmp(png_jmpbuf(png));

    png_init_io(png, fh);
    png_set_sig_bytes(png, 8);
    png_read_info(png, info);
    png_get_IHDR(png, info, &width, &height, &bitDepth, &color, 0, 0, 0);

	switch (png_get_color_type(png, info)) {
		case PNG_COLOR_TYPE_PALETTE:
            png_set_palette_to_rgb(png);
			break;
		case PNG_COLOR_TYPE_GRAY:
            png_set_gray_to_rgb(png);
			break;
		case PNG_COLOR_TYPE_GRAY_ALPHA:
			break;
		case PNG_COLOR_TYPE_RGB:
            if(png_get_valid(png, info, PNG_INFO_tRNS))
                png_set_tRNS_to_alpha(png);
            else
                png_set_filler(png, 0xff, PNG_FILLER_AFTER);
			break;
		case PNG_COLOR_TYPE_RGB_ALPHA:
			break;
		default:
            break;
	}

    if (bitDepth > 8)
        png_set_strip_16(png);

    png_read_update_info(png, info);

    /* Alloc Image Blob */
    rowBytes = png_get_rowbytes(png, info);
    blob = gdAllocArray(GDByte, width * height * 4);
    gdReturnValueIfNull(blob, NULL);

    /* Alloc Row Pointers */
    if (!(rowPointers = gdAllocArray(png_bytep, height))) {
        gdFree(blob);
        return(NULL);
    }

    /* Setup Row Pointers */
    for (i = 0; i < height; ++i)
        rowPointers[height - 1 - i] = (png_bytep) blob + i * (width * 4);

    /* Read the Whole Image */
    png_read_image(png, rowPointers);

    /* Free PNG Resources */
    gdFree(rowPointers);
    png_destroy_read_struct(&png, &info, NULL);

    /* Setup Image */
    if ((image = gdImageInit(image)) != NULL) {
        gdImageSetFormat(image, GD_IMAGE_FORMAT_RGBA); 
        gdImageSetSize(image, width, height);
        gdImageSetData(image, blob, rowBytes * height);
    }

    return(image);
}

GDImagePlugin __image_png = {
    .name = "PNG",
    .isFormat = __isPngImage,
    .mipMapCount = NULL,
    .readMipMap = NULL,
    .readImage = __pngImageRead,    
};

#endif /* GD_ENGINE_PNG_SUPPORT */

