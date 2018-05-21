#include "Context.h"

// TODO: Move this to a backend file.
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

// TODO: Move this to a backend file.
void CreateRenderingWindow(ra_rendering_context_t *context, ra_uint32_t windowWidth, ra_uint32_t windowHeight, const char *title)
{
	HINSTANCE currentInstance = GetModuleHandle(NULL);
	WNDCLASSEX windowClass;
	HWND windowHandle;
	HDC deviceContext;
	const char szClassName[] = "myWindowClass";

	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = 0;
	windowClass.lpfnWndProc = WndProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = currentInstance;
	windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = szClassName;
	windowClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&windowClass))
	{
		MessageBox(NULL, "Window registration failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		exit(1);
	}

	windowHandle = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		szClassName,
		title,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		windowWidth,
		windowHeight,
		NULL,
		NULL,
		currentInstance,
		NULL);

	if (!windowHandle)
	{
		MessageBox(NULL, "Error creating window!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		exit(1);
	}

	ShowWindow(windowHandle, SW_SHOW);

	deviceContext = GetDC(windowHandle);

	if (!deviceContext)
	{
		MessageBox(NULL, "Error creating device context", "Error!", MB_ICONEXCLAMATION | MB_OK);
		exit(1);
	}

	context->instance = currentInstance;
	context->windowHandle = windowHandle;
	context->deviceContext = deviceContext;
	context->windowWidth = windowWidth;
	context->windowHeight = windowHeight;

	SetWindowLong(windowHandle, GWL_USERDATA, (long)&context);
}

// TODO: Move this to a backend file.
int HandleMessage()
{
	MSG message;

	while (PeekMessage(&message, NULL, 0, 0, PM_NOREMOVE))
	{
		if (!GetMessage(&message, NULL, 0, 0))
		{
			return 1; // TODO: Properly handle message return codes
		}

		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return 0;
}

// TODO: Move this to a backend file.
void CleanupRenderingContext(ra_rendering_context_t *context)
{
	if (context->windowHandle)
	{

		if (context->deviceContext)
		{
			ReleaseDC(context->windowHandle, context->deviceContext);
		}

		DestroyWindow(context->windowHandle);
	}
}

// TODO: Move this to a backend file.
void FlushWindowContext(ra_rendering_context_t *context)
{
	if (!context->deviceContext)
	{
		return;
	}

	static BITMAPINFO bmi;
	memset(&bmi, 0, sizeof(bmi));

	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = context->windowWidth;
	bmi.bmiHeader.biHeight = -(static_cast<LONG>(context->windowHeight));
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biSizeImage = 0;

	SetDIBitsToDevice(
		context->deviceContext,
		0,
		0,
		context->windowWidth,
		context->windowHeight,
		0,
		0,
		0,
		context->windowHeight,
		context->framebuffer->pixels,
		&bmi,
		DIB_RGB_COLORS);
}
