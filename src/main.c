#define NOMINMAX            1
#define WIN32_LEAN_AND_MEAN 1
#define WIN32_MEAN_AND_LEAN 1
#define VC_EXTRALEAN        1
#include <windows.h>
#include <Timeapi.h>
#undef NOMINMAX
#undef WIN32_LEAN_AND_MEAN
#undef WIN32_MEAN_AND_LEAN
#undef VC_EXTRALEAN
#undef far
#undef near

#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <intrin.h>

typedef signed __int8  s8;
typedef signed __int16 s16;
typedef signed __int32 s32;
typedef signed __int64 s64;

typedef unsigned __int8  u8;
typedef unsigned __int16 u16;
typedef unsigned __int32 u32;
typedef unsigned __int64 u64;

typedef u8 bool;
#define true 1
#define false 0

typedef float f32;

#define ARRAY_SIZE(A) (sizeof(A)/sizeof(0[A]))

#include "math.h"

bool Running = false;

void
ErrorBox(char* format, ...)
{
  char buffer[1024];

  va_list args;
  va_start(args, format);
  vsnprintf(buffer, ARRAY_SIZE(buffer), format, args);
  va_end(args);

  MessageBoxA(0, buffer, "Error", MB_OK | MB_ICONERROR);
}

LRESULT
Wndproc(HWND window, UINT msg, WPARAM wparam, LPARAM lparam)
{
	LRESULT result;

	if (msg == WM_QUIT || msg == WM_CLOSE)
	{
    Running = false;
		result = 0;
	}
	else if (msg == WM_PAINT)
	{
		PAINTSTRUCT paint = {0};
		HDC dc = BeginPaint(window, &paint);

		EndPaint(window, &paint);
		result = 0;
	}
	else result = DefWindowProcA(window, msg, wparam, lparam);

	return result;
}

int
WinMain(HINSTANCE instance, HINSTANCE prev_instance, LPSTR cmd_line, int show_cmd)
{
	WNDCLASSA window_class = {
		.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC,
		.lpfnWndProc   = Wndproc,
		.cbClsExtra    = 0,
		.cbWndExtra    = 0,
		.hInstance     = instance,
		.hIcon         = 0,
		.hCursor       = 0,
		.hbrBackground = 0,
		.lpszMenuName  = 0,
		.lpszClassName = "CLST",
	};

  HWND window;
	if (!RegisterClassA(&window_class) ||
      !(window = CreateWindowA("CLST", "CLST", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, 0, 0)))
  {
    //// ERROR
    ErrorBox("Failed to create window");
  }
  else
  {
    ShowWindow(window, SW_SHOW);

    Running = true;
    while (Running)
    {
      for (MSG msg; PeekMessageA(&msg, 0, 0, 0, PM_REMOVE);)
      {
        Wndproc(window, msg.message, msg.wParam, msg.lParam);
      }
    }
  }

	return 0;
}
