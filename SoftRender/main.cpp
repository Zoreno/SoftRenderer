#include <iostream>

#include <Windows.h>

#include "RA.h"
#include <debugapi.h>

#define DLL_NAME ("Renderer.dll")

#define ra_LoadLibrary(handle) HINSTANCE handle = LoadLibrary(DLL_NAME); \
	if(!handle) \
	{ \
		OutputDebugStringA("Could not load DLL\n"); \
		return EXIT_FAILURE; \
	} 

#define ra_LoadFunction(handle, name) ra_##name = (ra_##name##_f)GetProcAddress(handle, #name); \
	if(!ra_##name) \
	{ \
		OutputDebugStringA("Could not load function "); \
		OutputDebugStringA(#name); \
		OutputDebugStringA("\n"); \
		return EXIT_FAILURE; \
	}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	ra_LoadLibrary(handle);

	ra_LoadFunction(handle, Initialize);
	ra_LoadFunction(handle, GetMajorVersion);
	ra_LoadFunction(handle, GetMinorVersion);

	ra_Initialize();

	uint32_t major_version = ra_GetMajorVersion();
	uint32_t minor_version = ra_GetMinorVersion();

	return EXIT_SUCCESS;
}