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

#define CLST_NAME "CLST"

typedef signed __int8  s8;
typedef signed __int16 s16;
typedef signed __int32 s32;
typedef signed __int64 s64;

typedef unsigned __int8  u8;
typedef unsigned __int16 u16;
typedef unsigned __int32 u32;
typedef unsigned __int64 u64;

typedef s64 smm;
typedef u64 umm;

typedef u8 bool;
#define false 0
#define true 1

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 1024

#define SCREEN_SIZE 128
u32 ScreenBuffers[2][SCREEN_SIZE*SCREEN_SIZE];
u32* Backbuffer;

#define LEVEL_SIZE 16
u8 Level[LEVEL_SIZE*LEVEL_SIZE] = {
	10, 10, 10, 10, 10, 10, 10, 10, 10, 10,  7,  0,  0,  0,  9, 10,
	10,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10,
	10,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10,
	10,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10,
	10,  0,  0,  0,  0,  0,  0,  2, 10, 10, 10,  5,  0,  0,  0, 10,
	10,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10,  0,  0,  0, 10,
	10,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10,  0,  0,  0, 10,
	10, 10, 10,  6,  0,  0,  0,  0,  0,  0,  0,  8,  0,  0,  0, 10,
	10,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10,
	10,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10,
	10,  0,  0,  0,  2, 10, 10,  6,  0,  0,  0,  0,  0,  0,  0, 10,
	10,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10,
	10,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3, 10, 10, 10,
	10,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 10, 10, 10,
	10,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3, 10, 10, 10, 10, 10,
	10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
};

#define TILE_SIZE 8
u8 Tiles[256][TILE_SIZE*TILE_SIZE] = {
	[0] = {0},
	[1] = {
		0, 1, 1, 1, 1, 1, 1, 0,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		0, 1, 1, 1, 1, 1, 1, 0,
	},
	[2] = {
		0, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		0, 1, 1, 1, 1, 1, 1, 1,
	},
	[3] = {
		0, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
	},
	[4] = {
		0, 1, 1, 1, 1, 1, 1, 0,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
	},
	[5] = {
		1, 1, 1, 1, 1, 1, 1, 0,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
	},
	[6] = {
		1, 1, 1, 1, 1, 1, 1, 0,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 0,
	},
	[7] = {
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 0,
	},
	[8] = {
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		0, 1, 1, 1, 1, 1, 1, 0,
	},
	[9] = {
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		0, 1, 1, 1, 1, 1, 1, 1,
	},
	[10] = {
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
	},
};

u32 ColorPalette[16] = {
	[0] = 0,
	[1] = 0xDFDFDF,
};

LRESULT
Wndproc(HWND window, UINT msg, WPARAM wparam, LPARAM lparam)
{
	LRESULT result;

	if (msg == WM_CLOSE)
	{
		DestroyWindow(window);
		PostQuitMessage(0);
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
WinMain(HINSTANCE instance, HINSTANCE pre_instance, LPSTR cmd_line, int show_cmd)
{
	bool failed_setup = false;

	HWND window = 0;
	{ /// Setup window
		WNDCLASSA window_class = {
			.style         = CS_OWNDC,
			.lpfnWndProc   = Wndproc,
			.cbClsExtra    = 0,
			.cbWndExtra    = 0,
			.hInstance     = instance,
			.hIcon         = 0,
			.hCursor       = 0,
			.hbrBackground = CreateSolidBrush(0),
			.lpszMenuName  = 0,
			.lpszClassName = CLST_NAME,
		};

		if (RegisterClassA(&window_class))
		{
			window = CreateWindowA(CLST_NAME, CLST_NAME, WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, 0, 0);
		}

		if (window == 0)
		{
			//// ERROR: Failed to create window
			failed_setup = true;
		}
		else ShowWindow(window, SW_SHOW);
	}

	if (!failed_setup)
	{
		RECT client_rect;
		GetClientRect(window, &client_rect);
		Backbuffer = ScreenBuffers[0];

		bool is_running = true;
		while (is_running)
		{
			MSG msg;
			while (PeekMessageA(&msg, 0, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT)
				{
					is_running = false;
					break;
				}
				else Wndproc(window, msg.message, msg.wParam, msg.lParam);
			}

			for (umm i = 0; i < SCREEN_SIZE*SCREEN_SIZE; ++i) Backbuffer[i] = 0;

			for (umm y = 0; y < LEVEL_SIZE; ++y)
			{
				for (umm x = 0; x < LEVEL_SIZE; ++x)
				{
					for (umm j = 0; j < TILE_SIZE; ++j)
					{
						for (umm i = 0; i < TILE_SIZE; ++i)
						{
							u8 tile = Level[y*LEVEL_SIZE + x];
							Backbuffer[(y*TILE_SIZE + j)*SCREEN_SIZE + x*TILE_SIZE + i] = ColorPalette[Tiles[tile][j*TILE_SIZE + i]];
						}
					}
				}
			}

			HDC dc = GetDC(window);

      BITMAPINFO bitmap_info = {
        .bmiHeader = {
          .biSize        = sizeof(BITMAPINFOHEADER),
          .biWidth       = SCREEN_SIZE,
          .biHeight      = -SCREEN_SIZE,
          .biPlanes      = 1,
          .biBitCount    = 32,
          .biCompression = BI_RGB,
        },
      };

      StretchDIBits(dc, 0, 0, client_rect.right - client_rect.left, client_rect.bottom - client_rect.top, 0, 0, SCREEN_SIZE, SCREEN_SIZE, Backbuffer, &bitmap_info, DIB_RGB_COLORS, SRCCOPY);

      ReleaseDC(window, dc);
			
			Backbuffer = (Backbuffer == ScreenBuffers[0] ? ScreenBuffers[1] : ScreenBuffers[0]);
		}
	}

	return 0;
}
