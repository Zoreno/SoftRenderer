#pragma once

#include "RA_common.h"
#include "Vertex.h"

// TODO: Separate framebuffers and textures.

// TODO: Much of the content of this file should be moved to a rasterizer file.

typedef struct _ra_bitmap
{
	ra_int32_t width;
	ra_int32_t height;
	ra_int32_t bpp;

	unsigned char *pixels;

	// This may also be represented by a char/int array
	float *depthBuffer;

	struct _ra_bitmap *texture;
} ra_bitmap_t;

ra_bitmap_t *CreateBitmap(ra_int32_t width, ra_int32_t height, ra_int32_t bpp);

ra_bitmap_t *CreateBitmapFromTGAImage(const char *filePath);

void DestroyBitmap(ra_bitmap_t *bitmap);

void ClearBitmap(ra_bitmap_t *bitmap, ra_uint8_t *color, bool clearColor = true, bool clearDepth = true);

void DrawPixel(
	ra_bitmap_t *bitmap,
	ra_int32_t x,
	ra_int32_t y,
	ra_uint8_t red,
	ra_uint8_t green,
	ra_uint8_t blue,
	ra_uint8_t alpha);


void CopyPixel(
	ra_bitmap_t *dest,
	ra_int32_t destX,
	ra_int32_t destY,
	ra_bitmap_t *src,
	ra_int32_t srcX,
	ra_int32_t srcY);

void DrawTriangle(ra_bitmap_t *bitmap, ra_vertex_t v1, ra_vertex_t v2, ra_vertex_t v3);