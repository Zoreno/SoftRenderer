#pragma once

#include "RA_common.h"

extern "C"
{

#ifdef RENDERER_EXPORTS
#define RA_API __declspec(dllexport)
#else
#define RA_API __declspec(dllimport)
#endif

	void RA_API Initialize();

	ra_uint32_t RA_API GetMajorVersion();
	ra_uint32_t RA_API GetMinorVersion();

}