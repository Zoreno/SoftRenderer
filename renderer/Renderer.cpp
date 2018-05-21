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
			{ -1.0f, -1.0f, 0.0f, 1.0f },
			{ 1.0f, 0.0f, 0.0f, 1.0f },
			{ 0.0f, 0.0f, 0.0f, 0.0f }
		};

		ra_vertex_t mid =
		{
			{ 0.0f, 1.0f, 0.0f, 1.0f },
			{ 0.0f, 1.0f, 0.0f, 1.0f },
			{ 1.0f, 0.0f, 0.0f, 0.0f }
		};

		ra_vertex_t bot =
		{
			{ 1.0f, -1.0f, 0.0f, 1.0f },
			{ 0.0f, 0.0f, 1.0f, 1.0f },
			{ 1.0f, 1.0f, 0.0f, 0.0f }
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

			ra_matrix4f_t translation1 = InitTranslation(0.f, 0.f, 4.0 + 14.f * sin(0.01f * deltaTime));
			ra_matrix4f_t translation2 = InitTranslation(0.f, 1.f, 4.f);
			ra_matrix4f_t rotation = InitRotation(0.f, static_cast<float>(deltaTime), 0.f);
			//ra_matrix4f_t rotation = InitRotation(0.f, 0.0f, 0.f);

			ra_matrix4f_t model1 = Multiply(translation1, rotation);
			ra_matrix4f_t model2 = Multiply(translation2, rotation);

			ra_matrix4f_t mp1 = Multiply(proj, model1);
			ra_matrix4f_t mp2 = Multiply(proj, model2);

			ra_vertex_t vert1 = top;
			ra_vertex_t vert2 = mid;
			ra_vertex_t vert3 = bot;
			vert1.position = Transform(top.position, mp1);
			vert2.position = Transform(mid.position, mp1);
			vert3.position = Transform(bot.position, mp1);

			DrawTriangle(_context.framebuffer, vert1, vert2, vert3);

			vert1.position = Transform(top.position, mp2);
			vert2.position = Transform(mid.position, mp2);
			vert3.position = Transform(bot.position, mp2);

			DrawTriangle(_context.framebuffer, vert1, vert2, vert3);

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