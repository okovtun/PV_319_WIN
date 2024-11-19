#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<iostream>
#include"resource.h"

CONST CHAR g_sz_CLASS_NAME[] = "Calc PV_319";

CONST INT g_i_INTERVAL = 5;
CONST INT g_i_BUTTON_SIZE = 50;
CONST INT g_i_BUTTON_DOUBLE_SIZE = g_i_BUTTON_SIZE * 2 + g_i_INTERVAL;

CONST INT g_i_DISPLAY_WIDTH = g_i_BUTTON_SIZE * 5 + g_i_INTERVAL * 4;
CONST INT g_i_DISPLAY_HEIGHT = 22;


CONST INT g_i_START_X = 10;
CONST INT g_i_START_Y = 10;
CONST INT g_i_BUTTON_START_X = g_i_START_X;
CONST INT g_i_BUTTON_START_Y = g_i_START_Y + g_i_DISPLAY_HEIGHT + g_i_INTERVAL;
CONST INT g_i_OPERATION_BUTTON_START_X = g_i_START_X + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 3;
CONST INT g_i_OPERATION_BUTTON_START_Y = g_i_BUTTON_START_Y;
CONST INT g_i_CONTROL_BUTTON_START_X = g_i_START_X + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 4;
CONST INT g_i_CONTROL_BUTTON_START_Y = g_i_BUTTON_START_Y;

CONST INT g_i_WINDOW_WIDTH = g_i_DISPLAY_WIDTH + g_i_START_X * 2 + 16;
CONST INT g_i_WINDOW_HEIGHT = g_i_DISPLAY_HEIGHT + g_i_START_Y * 2 + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 4 + 38;

CONST CHAR* g_OPERATIONS[] = { "+", "-", "*", "/" };

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
		WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT,	//Position: X, Y
		g_i_WINDOW_WIDTH, g_i_WINDOW_HEIGHT,	//Size:		Width, Height
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
		AllocConsole();
		freopen("CONOUT$", "w", stdout);

		HWND hEdit = CreateWindowEx
		(
			NULL, "Edit", "0",
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT,
			10, 10,
			g_i_DISPLAY_WIDTH, g_i_DISPLAY_HEIGHT,
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
					(HMENU)(IDC_BUTTON_1 + i + j),
					GetModuleHandle(NULL),
					NULL
				);
			}
		}
		CreateWindowEx
		(
			NULL, "Button", "0",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_BUTTON_START_X,
			g_i_BUTTON_START_Y + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 3,
			g_i_BUTTON_DOUBLE_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_0,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL, "Button", ".",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_BUTTON_START_X + g_i_BUTTON_DOUBLE_SIZE + g_i_INTERVAL,
			g_i_BUTTON_START_Y + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 3,
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_POINT,
			GetModuleHandle(NULL),
			NULL
		);

		for (int i = 0; i < 4; i++)
		{
			CreateWindowEx
			(
				NULL, "Button", g_OPERATIONS[i],
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				g_i_OPERATION_BUTTON_START_X,
				g_i_BUTTON_START_Y + (g_i_BUTTON_SIZE + g_i_INTERVAL)*(3 - i),
				g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
				hwnd,
				(HMENU)(IDC_BUTTON_PLUS + i),
				GetModuleHandle(NULL),
				NULL
			);
		}

		CreateWindowEx
		(
			NULL, "Button", "<-",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_CONTROL_BUTTON_START_X,
			g_i_CONTROL_BUTTON_START_Y,
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_BSP,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL, "Button", "C",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_CONTROL_BUTTON_START_X,
			g_i_CONTROL_BUTTON_START_Y + g_i_BUTTON_SIZE + g_i_INTERVAL,
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_CLEAR,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL, "Button", "=",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_CONTROL_BUTTON_START_X,
			g_i_CONTROL_BUTTON_START_Y + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 2,
			g_i_BUTTON_SIZE, g_i_BUTTON_DOUBLE_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_EQUAL,
			GetModuleHandle(NULL),
			NULL
		);

	}
	break;
	case WM_COMMAND:
	{
		CONST INT SIZE = 256;
		CHAR sz_display[SIZE] = {};
		CHAR sz_digit[2] = {};
		HWND hEditDisplay = GetDlgItem(hwnd, IDC_EDIT_DISPLAY);
		SendMessage(hEditDisplay, WM_GETTEXT, SIZE, (LPARAM)sz_display);
		if (LOWORD(wParam) >= IDC_BUTTON_0 && LOWORD(wParam) <= IDC_BUTTON_9)
		{
			sz_digit[0] = LOWORD(wParam) - IDC_BUTTON_0 + '0';
			if (strlen(sz_display) == 1 && sz_display[0] == '0')
				sz_display[0] = sz_digit[0];
			else
				strcat(sz_display, sz_digit);
			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
		}
		if (LOWORD(wParam) == IDC_BUTTON_POINT)
		{
			if (strchr(sz_display, '.'))break;
			strcat(sz_display, ".");
			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
		}
		//if (LOWORD(wParam) == IDC_EDIT_DISPLAY && HIWORD(wParam) == EN_SETFOCUS)SetFocus(hwnd);
		if (LOWORD(wParam) == IDC_BUTTON_BSP)
		{
			if (strlen(sz_display) == 1)sz_display[0] = '0';
			else sz_display[strlen(sz_display) - 1] = 0;
			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
		}
		if (LOWORD(wParam) == IDC_BUTTON_CLEAR)
		{
			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)"0");
		}
		SetFocus(hwnd);
	}
	break;
	case WM_KEYDOWN:
	{
		//if (wParam >= 0x30 && wParam <= 0x39)
			//SendMessage(hwnd, WM_COMMAND, wParam - 0x30 + IDC_BUTTON_0, 0);
		if (wParam >= '0' && wParam <= '9')
			SendMessage(hwnd, WM_COMMAND, wParam - '0' + IDC_BUTTON_0, 0);
		switch (wParam)
		{
		case VK_OEM_PERIOD: SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_POINT), 0); break;
		case VK_ESCAPE:		SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_CLEAR), 0); break;
		case VK_BACK:		SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_BSP), 0); break;
		}
	}
	break;
	////////////////////////////
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	default:	return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}