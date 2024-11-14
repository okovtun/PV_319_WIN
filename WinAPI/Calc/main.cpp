#include<Windows.h>
#include"resource.h"

CONST CHAR g_sz_CLASS_NAME[] = "Calc PV_319";

CONST INT g_i_BUTTON_SIZE = 50;
CONST INT g_i_INTERVAL = 5;

CONST INT g_i_DISPLAY_WIDTH = 384;
CONST INT g_i_DISPLAY_HEIGHT = 22;

CONST INT g_i_START_X = 10;
CONST INT g_i_START_Y = 10;
CONST INT g_i_BUTTON_START_X = g_i_START_X;
CONST INT g_i_BUTTON_START_Y = g_i_START_Y + g_i_DISPLAY_HEIGHT + g_i_INTERVAL;

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//1) Регистраци класса окна:

	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(wClass));

	wClass.style = 0;
	wClass.cbSize = sizeof(wClass);
	wClass.cbClsExtra = 0;
	wClass.cbWndExtra = 0;

	wClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wClass.hCursor = LoadCursor(hInstance, IDC_ARROW);
	wClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	//wClass.hbrBackground = CreateSolidBrush(RGB(0,0,200));

	wClass.hInstance = hInstance;
	wClass.lpszClassName = g_sz_CLASS_NAME;
	wClass.lpfnWndProc = (WNDPROC)WndProc;
	wClass.lpszMenuName = NULL;

	if (!RegisterClassEx(&wClass))
	{
		MessageBox(NULL, "Class registration failed!", NULL, MB_OK | MB_ICONERROR);
		return 0;
	}

	//2) Создание окна:
	HWND hwnd = CreateWindowEx
	(
		NULL,
		g_sz_CLASS_NAME,
		g_sz_CLASS_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,	//Position: X, Y
		CW_USEDEFAULT, CW_USEDEFAULT,	//Size:		Width, Height
		NULL,
		NULL,
		hInstance,
		NULL
	);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	//3) Запуск цикла сообщений:
	//https://learn.microsoft.com/en-us/windows/win32/winmsg/using-messages-and-message-queues
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		HWND hEdit = CreateWindowEx
		(
			NULL, "Edit", "",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			10, 10,
			384, 22,
			hwnd,
			(HMENU)IDC_EDIT_DISPLAY,
			GetModuleHandle(NULL),
			NULL
		);

		CHAR sz_digit[2] = "0";
		for (int i = 6; i >= 0; i -= 3)
		{
			for (int j = 0; j < 3; j++)
			{
				sz_digit[0] = 49 + i + j;	//49 - ASCII-код единицы.
				CreateWindowEx
				(
					NULL, "Button", sz_digit,
					WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
					g_i_BUTTON_START_X + j * (g_i_BUTTON_SIZE + g_i_INTERVAL),
					g_i_BUTTON_START_Y + (g_i_BUTTON_SIZE + g_i_INTERVAL) * (2 - i / 3),
					g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
					hwnd,
					(HMENU)IDC_BUTTON_1 + i + j,
					GetModuleHandle(NULL),
					NULL
				);
			}
		}
	}
	break;
	case WM_COMMAND:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	default:	return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}