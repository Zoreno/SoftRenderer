#include "Renderer.h"

#include <Windows.h>
#include <chrono>
#include <ctime>

#include "MathUtil.h"
#include "Vector.h"
#include "Matrix.h"

#include <iostream>
#include <fstream>
#include <vector>
#include "Gradient.h"
#include "Edge.h"
#include "Color.h"
#include "Context.h"
#include "Time.h"
#include "Bitmap.h"

//=============================================================================
// Rendering context struct
//=============================================================================

static ra_rendering_context_t _context;

//=============================================================================
// DLL API
//=============================================================================

extern "C" {

	void Initialize()
	{
		_context.majorVersion = 0;
		_context.minorVersion = 1;

		CreateRenderingWindow(&_context, 800, 600, "Title");

		_context.framebuffer = CreateBitmap(800, 600, 4);

		_context.framebuffer->texture = CreateBitmapFromTGAImage("../Res/texture.tga");

		ra_color_t clearColor = CreateColor(0, 0, 0);

		ra_vertex_t top =
		{
			{ -1.0f, 1.0f, 0.0f, 1.0f }, // Position
			{ 1.0f, 0.0f, 0.0f, 1.0f }, // Color (Not used at the moment)
			{ 0.0f, 1.0f, 0.0f, 0.0f } // Texture coordinates
		};

		ra_vertex_t mid =
		{
			{ 1.0f, 1.0f, 0.0f, 1.0f },
			{ 0.0f, 1.0f, 0.0f, 1.0f },
			{ 1.0f, 1.0f, 0.0f, 0.0f }
		};

		ra_vertex_t bot =
		{
			{ -1.0f, -1.0f, 0.0f, 1.0f },
			{ 0.0f, 0.0f, 1.0f, 1.0f },
			{ 0.0f, 0.0f, 0.0f, 0.0f }
		};

		ra_vertex_t extra =
		{
			{ 1.0f, -1.0f, 1.0f, 1.0f },
			{ 0.0f, 0.0f, 1.0f, 1.0f },
			{ 1.0f, 0.0f, 0.0f, 0.0f }
		};

		ra_matrix4f_t proj = InitPerspective(90.f, 800.f / 600.f, 0.1f, 1000.f);
		//ra_matrix4f_t proj = InitOrthographic(-1, 1, -1, 1, 0.1f, 1000.f);

		unsigned long long startTime = GetTime();

		while (true)
		{
			int retVal;

			retVal = HandleMessage();

			if (retVal != 0)
			{
				break;
			}

			// Draw Here

			unsigned long long deltaTime = GetTime() - startTime;

			deltaTime /= 10;

			ClearBitmap(_context.framebuffer, (ra_uint8_t *)&clearColor);

			ra_matrix4f_t translation1 = InitTranslation(0.f, 0.f, 3.0 + sin(0.01f * deltaTime));
			ra_matrix4f_t rotation = InitRotation(0.f, static_cast<float>(deltaTime), 0.f);
			//ra_matrix4f_t rotation = InitRotation(0.f, 0.0f, 0.f);

			ra_matrix4f_t model1 = Multiply(translation1, rotation);

			ra_matrix4f_t mp1 = Multiply(proj, model1);

			ra_vertex_t vert1 = top;
			ra_vertex_t vert2 = mid;
			ra_vertex_t vert3 = bot;
			ra_vertex_t vert4 = extra;
			vert1.position = Transform(top.position, mp1);
			vert2.position = Transform(mid.position, mp1);
			vert3.position = Transform(bot.position, mp1);
			vert4.position = Transform(extra.position, mp1);

			std::vector<ra_vertex_t> vertices;
			vertices.push_back(vert1);
			vertices.push_back(vert2);
			vertices.push_back(vert3);
			vertices.push_back(vert4);

			// TODO: 
			// Instead of calling DrawTriangle, we should put all the vertices into a buffer
			// and call the DrawBuffer command, which will take in the vertices and apply something
			// like a vertex shader to each of the objects. The resulting vertices should then be fed
			// into a tesselation stage, where the vertices are converted to smaller primitives. 
			// Optionally, a geometry shader could be used to add or remove vertices.
			//
			// The resulting vertices the go to the vertex post-processing stage, where transform
			// feedback and clipping might take place. Perspective divide and depth clamping may
			// also be performed.
			//
			// The vertices are then assemblied to primitives, here triangles, which are fed to the
			// rasterizer, which generates fragments. The fragments are fed into a fragment-shader
			// like stage, which can apply per-fragment operations to the fragments. The result
			// is stored in a framebuffer which can then be used as a texture or swapped to screen.
			DrawTriangleStrip(_context.framebuffer, &vertices[0], vertices.size());

			FlushWindowContext(&_context);

		}

		DestroyBitmap(_context.framebuffer);

		CleanupRenderingContext(&_context);
	}

	ra_uint32_t GetMajorVersion()
	{
		return _context.majorVersion;
	}

	ra_uint32_t GetMinorVersion()
	{
		return _context.minorVersion;
	}
}

//=============================================================================
// End of file
//=============================================================================