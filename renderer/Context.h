#pragma once

#include "RA_common.h"

#include <Windows.h>
#include "Bitmap.h"

/*

typedef struct _ra_framebuffer
{
GLuint name;

ra_int32_t width;
ra_int32_t height;
ra_int32_t bpp;

ra_uint8_t *clearColor;

// Alpha Testing
bool alphaEnabled;
ALPHA_FUNC alphaFunc;
float AlphaRef;

// Blending
bool blendingEnabled;
float blendColor[4];
GLBLEND srcRGB;
GLBLEND destRGB;
GLBLEND srcA;
GLBLEND destA;
GLBLEND EquationRGB;
GLBLEND EquationA;

unsigned char *colorBuffer;

// Depth
bool depthEnabled;
DEPTH_FUNC depthFunc;
float depthClear;
bool depthMask;

float *depthBuffer;

} ra_framebuffer_t;

typedef struct _ra_texture_image
{
FORMAT internalFormat;
FORMAT baseFormat;

ra_int32_t border;

ra_int32_t width;
ra_int32_t height;
ra_int32_t depth; // For 3D textures.

ra_int32_t widthlog2;
ra_int32_t heightlog2;
ra_int32_t depthlog2; // For 3D textures.

ra_int32_t level; // For mipmapping
ra_int32_t face;

ra_int32_t bpp;

unsigned char *colorBuffer;
} ra_texture_image_t;

typedef struct _ra_texture_sampler
{
GLuint name;

GL_WRAP_MODE wrapS;
GL_WRAP_MODE wrapT;
GL_WRAP_MODE wrapR;
GL_FILTER minFilter;
GL_FILTER maxFilter;

Color borderColor;

COMPAREMODE compareMode;
COMPAREFUNC compareFunc;


...

} ra_texture_sampler_t;

typedef struct _ra_texture_object
{
GL_TARGET target;
GL_DEPTH_MODE depthMode;

ra_texture_sampler_t	*sampler;

ra_texture_image_t		**images;

} ra_texture_object_t;

*/

typedef struct _ra_rendering_context
{
	ra_uint32_t majorVersion;
	ra_uint32_t minorVersion;

	ra_uint32_t windowWidth;
	ra_uint32_t windowHeight;

	ra_bitmap_t *framebuffer;

	// TODO: Move these windows specific state variables to a separate backend implementation struct.
	HINSTANCE instance;
	HWND windowHandle;
	HDC deviceContext;
} ra_rendering_context_t;

// These are all backend-dependent functions. These should not be in the renderer.
void CreateRenderingWindow(ra_rendering_context_t *context, ra_uint32_t windowWidth, ra_uint32_t windowHeight, const char *title);
int HandleMessage();
void CleanupRenderingContext(ra_rendering_context_t *context);
void FlushWindowContext(ra_rendering_context_t *context);