#include "Bitmap.h"

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "Vertex.h"
#include "Gradient.h"
#include "Edge.h"
#include "Matrix.h"

ra_bitmap_t *CreateBitmap(ra_int32_t width, ra_int32_t height, ra_int32_t bpp)
{
	ra_bitmap_t *bitmap = (ra_bitmap_t *)malloc(sizeof(ra_bitmap_t));

	if (!bitmap)
	{
		return nullptr;
	}

	bitmap->width = width;
	bitmap->height = height;
	bitmap->bpp = bpp;

	bitmap->pixels = (unsigned char *)malloc(width * height * bpp * sizeof(unsigned char));

	if (!bitmap->pixels)
	{
		free(bitmap);

		return nullptr;
	}

	bitmap->depthBuffer = (float *)malloc(width * height * sizeof(float));

	if (!bitmap->depthBuffer)
	{
		free(bitmap->pixels);
		free(bitmap);

		return nullptr;
	}

	bitmap->texture = nullptr;

	return bitmap;
}

typedef union PixelInfo
{
	std::uint32_t Colour;
	struct
	{
		std::uint8_t R, G, B, A;
	};
} *PPixelInfo;

ra_bitmap_t *CreateBitmapFromTGAImage(const char *filePath)
{
	ra_bitmap_t *bitmap = (ra_bitmap_t *)malloc(sizeof(ra_bitmap_t));

	if (!bitmap)
	{
		return nullptr;
	}

	std::fstream hFile(filePath, std::ios::in | std::ios::binary);

	if (!hFile.is_open())
	{
		free(bitmap);
		return nullptr;
	}

	std::uint8_t Header[18] = { 0 };
	std::vector<std::uint8_t> ImageData;
	static std::uint8_t DeCompressed[12] = { 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };
	static std::uint8_t IsCompressed[12] = { 0x0, 0x0, 0xA, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };

	hFile.read(reinterpret_cast<char*>(&Header), sizeof(Header));

	int size;

	if (!std::memcmp(DeCompressed, &Header, sizeof(DeCompressed)))
	{
		bitmap->bpp = Header[16];
		bitmap->width = Header[13] * 256 + Header[12];
		bitmap->height = Header[15] * 256 + Header[14];
		size = ((bitmap->width * bitmap->bpp + 31) / 32) * 4 * bitmap->height;

		if ((bitmap->bpp != 24) && (bitmap->bpp != 32))
		{
			hFile.close();
			throw std::invalid_argument("Invalid File Format. Required: 24 or 32 Bit Image.");
		}

		ImageData.resize(size);
		hFile.read(reinterpret_cast<char*>(ImageData.data()), size);
	}
	else if (!std::memcmp(IsCompressed, &Header, sizeof(IsCompressed)))
	{
		bitmap->bpp = Header[16];
		bitmap->width = Header[13] * 256 + Header[12];
		bitmap->height = Header[15] * 256 + Header[14];
		size = ((bitmap->width * bitmap->bpp + 31) / 32) * 4 * bitmap->height;

		if ((bitmap->bpp != 24) && (bitmap->bpp != 32))
		{
			hFile.close();
			throw std::invalid_argument("Invalid File Format. Required: 24 or 32 Bit Image.");
		}

		PixelInfo Pixel = { 0 };
		int CurrentByte = 0;
		std::size_t CurrentPixel = 0;
		std::uint8_t ChunkHeader = { 0 };
		int BytesPerPixel = (bitmap->bpp / 8);
		ImageData.resize(bitmap->width * bitmap->height * sizeof(PixelInfo));

		do
		{
			hFile.read(reinterpret_cast<char*>(&ChunkHeader), sizeof(ChunkHeader));

			if (ChunkHeader < 128)
			{
				++ChunkHeader;
				for (int I = 0; I < ChunkHeader; ++I, ++CurrentPixel)
				{
					hFile.read(reinterpret_cast<char*>(&Pixel), BytesPerPixel);

					ImageData[CurrentByte++] = Pixel.B;
					ImageData[CurrentByte++] = Pixel.G;
					ImageData[CurrentByte++] = Pixel.R;
					if (bitmap->bpp > 24) ImageData[CurrentByte++] = Pixel.A;
				}
			}
			else
			{
				ChunkHeader -= 127;
				hFile.read(reinterpret_cast<char*>(&Pixel), BytesPerPixel);

				for (int I = 0; I < ChunkHeader; ++I, ++CurrentPixel)
				{
					ImageData[CurrentByte++] = Pixel.B;
					ImageData[CurrentByte++] = Pixel.G;
					ImageData[CurrentByte++] = Pixel.R;
					if (bitmap->bpp > 24) ImageData[CurrentByte++] = Pixel.A;
				}
			}
		} while (CurrentPixel < (bitmap->width * bitmap->height));
	}
	else
	{
		hFile.close();
		throw std::invalid_argument("Invalid File Format. Required: 24 or 32 Bit TGA File.");
	}

	hFile.close();
	bitmap->pixels = (unsigned char *)malloc(size);

	memcpy(bitmap->pixels, &ImageData[0], size);

	bitmap->bpp /= 8;

	bitmap->depthBuffer = nullptr;
	bitmap->texture = nullptr;

	return bitmap;
}

void DestroyBitmap(ra_bitmap_t *bitmap)
{
	if (bitmap)
	{
		if (bitmap->pixels)
		{
			free(bitmap->pixels);
		}

		if (bitmap->depthBuffer)
		{
			free(bitmap->depthBuffer);
		}

		if (bitmap->texture)
		{
			DestroyBitmap(bitmap->texture);
		}

		free(bitmap);
	}
}

void ClearBitmap(ra_bitmap_t *bitmap, ra_uint8_t *color, bool clearColor, bool clearDepth)
{
	// WARNING: This assumes that the format of the bitmap is the same as the color struct and that the
	// depth buffer is represented as floating point.

	if (clearColor)
	{
		const ra_int32_t size = bitmap->width * bitmap->height * bitmap->bpp;

		// This can be optimized with SIMD
		for (ra_int32_t i = 0; i < size; i += bitmap->bpp)
		{
			bitmap->pixels[i] = color[0];
			bitmap->pixels[i + 1] = color[1];
			bitmap->pixels[i + 2] = color[2];
			bitmap->pixels[i + 3] = color[3];
		}
	}

	if (clearDepth)
	{
		const ra_int32_t size = bitmap->width * bitmap->height;

		if (!bitmap->depthBuffer)
		{
			return;
		}

		for (ra_int32_t i = 0; i < size; ++i)
		{
			// TODO: Read this value from context.
			// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glClearDepth.xhtml
			bitmap->depthBuffer[i] = std::numeric_limits<float>::infinity();
		}

	}

}

static void ClipPolygonComponent(
	const std::vector<ra_vertex_t> &vertices,
	int componentIndex,
	float componentFactor,
	std::vector<ra_vertex_t> &result)
{
	ra_vertex_t previousVertex = vertices.at(vertices.size() - 1);
	float previousComponent = VertexGet(previousVertex, componentIndex) * componentFactor;
	bool previousInside = previousComponent <= previousVertex.position.w;

	auto it = vertices.begin();

	while (it != vertices.end())
	{
		ra_vertex_t currentVertex = *it;

		float currentComponent = VertexGet(currentVertex, componentIndex) * componentFactor;
		bool currentInside = currentComponent <= currentVertex.position.w;

		if (currentInside ^ previousInside)
		{
			float lerpAmt = (previousVertex.position.w - previousComponent) /
				((previousVertex.position.w - previousComponent) - (currentVertex.position.w - currentComponent));

			result.push_back(Lerp(previousVertex, currentVertex, lerpAmt));
		}

		if (currentInside)
		{
			result.push_back(currentVertex);
		}

		previousComponent = currentComponent;
		previousVertex = currentVertex;
		previousInside = currentInside;

		++it;
	}
}

static bool ClipPolygonAxis(
	std::vector<ra_vertex_t> &vertices,
	std::vector<ra_vertex_t> &auxillaryList,
	int componentIndex)
{
	ClipPolygonComponent(vertices, componentIndex, 1.0f, auxillaryList);
	vertices.clear();

	if (auxillaryList.empty())
	{
		return false;
	}

	ClipPolygonComponent(auxillaryList, componentIndex, -1.f, vertices);
	auxillaryList.clear();

	return !vertices.empty();
}

void DrawPixel(
	ra_bitmap_t *bitmap,
	ra_int32_t x,
	ra_int32_t y,
	ra_uint8_t red,
	ra_uint8_t green,
	ra_uint8_t blue,
	ra_uint8_t alpha)
{
	if (x >= bitmap->width)
	{
		return;
	}

	if (y >= bitmap->height)
	{
		return;
	}

	ra_int32_t offset = (bitmap->width * y + x) * bitmap->bpp;

	// TODO: Swizzling with different bitmap formats
	bitmap->pixels[offset + 0] = red;
	bitmap->pixels[offset + 1] = green;
	bitmap->pixels[offset + 2] = blue;
	bitmap->pixels[offset + 3] = alpha;
}

void CopyPixel(
	ra_bitmap_t *dest,
	ra_int32_t destX,
	ra_int32_t destY,
	ra_bitmap_t *src,
	ra_int32_t srcX,
	ra_int32_t srcY)
{
	if (destX < 0)
	{
		return;
	}

	if (destY < 0)
	{
		return;
	}

	if (destX >= dest->width)
	{
		return;
	}

	if (destY >= dest->height)
	{
		return;
	}

	if (srcX < 0)
	{
		return;
	}

	if (srcY < 0)
	{
		return;
	}

	if (srcX >= src->width)
	{
		return;
	}

	if (srcY >= src->height)
	{
		return;
	}

	// TODO: Format swizzling.

	ra_int32_t destOffset = (dest->width * destY + destX) * dest->bpp;
	ra_int32_t srcOffset = (src->width * srcY + srcX) * src->bpp;

	dest->pixels[destOffset + 0] = src->pixels[srcOffset + 0];
	dest->pixels[destOffset + 1] = src->pixels[srcOffset + 1];
	dest->pixels[destOffset + 2] = src->pixels[srcOffset + 2];
	dest->pixels[destOffset + 3] = src->pixels[srcOffset + 3];

}

static void DrawScanLine(ra_bitmap_t *bitmap, ra_gradients_t gradients, ra_edge_t left, ra_edge_t right, int j)
{
	if (j >= bitmap->height)
	{
		j = bitmap->height - 1;
	}

	int xMin = static_cast<int>(std::ceil(left.x));
	int xMax = static_cast<int>(std::ceil(right.x));

	float xPrestep = xMin - left.x;

	ra_vector4f_t minColor = left.color + gradients.colorXStep * xPrestep;
	ra_vector4f_t maxColor = right.color + gradients.colorXStep * xPrestep;

	float xDist = right.x - left.x;
	float texCoordXXStep = (right.texCoordX - left.texCoordX) / xDist;
	float texCoordYXStep = (right.texCoordY - left.texCoordY) / xDist;
	float oneOverZStep = (right.oneOverZ - left.oneOverZ) / xDist;
	float depthStep = (right.depth - left.depth) / xDist;

	float texCoordX = left.texCoordX + gradients.texCoordXXStep * xPrestep;
	float texCoordY = left.texCoordY + gradients.texCoordYXStep * xPrestep;
	float oneOverZ = left.oneOverZ + gradients.oneOverZXStep * xPrestep;
	float depth = left.depth + gradients.depthXStep * xPrestep;

	float lerpAmount = 0.0f;
	float lerpStep = 1.0f / (float)(xMax - xMin);

	// Here we can take in to account the Polygon Mode

	for (int i = xMin; i < xMax; ++i)
	{
		ra_int32_t depthIndex = j * bitmap->width + i;

		// If there is no bitmap, use colors
		if (!bitmap->texture)
		{
			ra_vector4f_t interpolatedColor = Lerp(minColor, maxColor, lerpAmount);

			ra_uint8_t red = static_cast<ra_uint8_t>(interpolatedColor.x * 255.f + 0.5f);
			ra_uint8_t green = static_cast<ra_uint8_t>(interpolatedColor.y * 255.f + 0.5f);
			ra_uint8_t blue = static_cast<ra_uint8_t>(interpolatedColor.z * 255.f + 0.5f);
			ra_uint8_t alpha = static_cast<ra_uint8_t>(interpolatedColor.w * 255.f + 0.5f);

			if (depth < bitmap->depthBuffer[depthIndex])
			{
				DrawPixel(bitmap, i, j, red, green, blue, alpha);
				bitmap->depthBuffer[depthIndex] = depth;
			}

			lerpAmount += lerpStep;
		}
		else
		{
			int srcX = static_cast<int>((texCoordX / oneOverZ) * (bitmap->texture->width - 1) + 0.5f);
			int srcY = static_cast<int>((texCoordY / oneOverZ) * (bitmap->texture->height - 1) + 0.5f);

			// TODO: Setup sampler structure so that we can specify how to interpret 
			// texture accesses outside bounds, i.e. clamp_to_edge or tiling, and multiple formats.
			// This can also include super-sampling of textures. Swizzling may also be done here.

			// pixel = SampleTexture(textureUnit->texture, srcX, srcY, textureUnit->sampler);
			// DrawPixel(dest, i, j, pixel);

			// This may also be the place to insert some fragment shader-like code to have the user specify how the
			// coloring of the fragment is done.

			// This maybe should be replaced with a BitBlt function since it takes a lot of time.

			// TODO: Implement the proper depth test from the context parameters
			// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glDepthFunc.xhtml
			// https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glDepthMask.xml
			// https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glDepthRange.xml
			// https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glClearDepth.xml
			if (depth < bitmap->depthBuffer[depthIndex])
			{
				// TODO: implement blending
				// https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glBlendFunc.xml
				// https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glBlendColor.xml
				// https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glBlendEquation.xml
				// https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glBlendEquationSeparate.xml
				CopyPixel(bitmap, i, j, (ra_bitmap_t *)bitmap->texture, srcX, srcY);
				bitmap->depthBuffer[depthIndex] = depth;
			}

			texCoordX += texCoordXXStep;
			texCoordY += texCoordYXStep;
			oneOverZ += oneOverZStep;
		}

		depth += depthStep;
	}
}

static void ScanEdge(ra_bitmap_t *bitmap, ra_gradients_t gradients, ra_edge_t *a, ra_edge_t *b, bool handedness)
{
	ra_edge_t *left = a;
	ra_edge_t *right = b;

	if (handedness)
	{
		ra_edge_t *temp = left;
		left = right;
		right = temp;
	}

	int yStart = b->yStart;
	int yEnd = b->yEnd;

	for (int j = yStart; j < yEnd; ++j)
	{
		DrawScanLine(bitmap, gradients, *left, *right, j);

		EdgeStep(left);
		EdgeStep(right);
	}
}

static void ScanTriangle(ra_bitmap_t *bitmap, ra_vertex_t minYvert, ra_vertex_t midYvert, ra_vertex_t maxYvert, bool handedness)
{
	ra_gradients_t gradients = CreateGradients(minYvert, midYvert, maxYvert);

	ra_edge_t topToBottom = CreateEdge(gradients, minYvert, maxYvert, 0);
	ra_edge_t topToMiddle = CreateEdge(gradients, minYvert, midYvert, 0);
	ra_edge_t middleToBottom = CreateEdge(gradients, midYvert, maxYvert, 1);

	ScanEdge(bitmap, gradients, &topToBottom, &topToMiddle, handedness);
	ScanEdge(bitmap, gradients, &topToBottom, &middleToBottom, handedness);

}

static void FillTriangle(ra_bitmap_t *bitmap, ra_vertex_t v1, ra_vertex_t v2, ra_vertex_t v3)
{
	ra_matrix4f_t screenSpaceTransform = InitScreenSpaceTransform(
		static_cast<float>(bitmap->width) / 2.f,
		static_cast<float>(bitmap->height) / 2.f);

	ra_vertex_t minYvert = Transform(v1, screenSpaceTransform);
	ra_vertex_t midYvert = Transform(v2, screenSpaceTransform);
	ra_vertex_t maxYvert = Transform(v3, screenSpaceTransform);

	minYvert = PerspectiveDivide(minYvert);
	midYvert = PerspectiveDivide(midYvert);
	maxYvert = PerspectiveDivide(maxYvert);

	// This is backface culling. This should get parameters from context such as
	// CLOCKWISE/COUNTERCLOCKWISE and BACK/FRONT/BACK_AND_FRONT
	if (TriangleVertexArea(minYvert, maxYvert, midYvert) >= 0)
	{
		return;
	}

	if (maxYvert.position.y < midYvert.position.y)
	{
		std::swap(maxYvert, midYvert);
	}

	if (midYvert.position.y < minYvert.position.y)
	{
		std::swap(midYvert, minYvert);
	}

	if (maxYvert.position.y < midYvert.position.y)
	{
		std::swap(maxYvert, midYvert);
	}

	float area = TriangleVertexArea(minYvert, maxYvert, midYvert);

	bool handedness = area >= 0;

	ScanTriangle(bitmap, minYvert, midYvert, maxYvert, handedness);
}

void DrawTriangle(ra_bitmap_t *bitmap, ra_vertex_t v1, ra_vertex_t v2, ra_vertex_t v3)
{
	bool v1Inside = VertexIsInsideViewFrustum(v1);
	bool v2Inside = VertexIsInsideViewFrustum(v2);
	bool v3Inside = VertexIsInsideViewFrustum(v3);

	if (v1Inside && v2Inside && v3Inside)
	{
		FillTriangle(bitmap, v1, v2, v3);
		return;
	}

	if (!v1Inside && !v2Inside && !v3Inside)
	{
		return;
	}

	std::vector<ra_vertex_t> vertices;
	std::vector<ra_vertex_t> auxillaryList;

	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);

	if (ClipPolygonAxis(vertices, auxillaryList, 0) &&
		ClipPolygonAxis(vertices, auxillaryList, 1) &&
		ClipPolygonAxis(vertices, auxillaryList, 2))
	{
		ra_vertex_t initialVertex = vertices.at(0);

		for (int i = 1; i < vertices.size() - 1; ++i)
		{
			FillTriangle(bitmap, initialVertex, vertices.at(i), vertices.at(i + 1));
		}
	}
}
