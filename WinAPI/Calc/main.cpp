#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<iostream>
#include<Shlwapi.h>
#include"resource.h"

#pragma comment (lib, "Shlwapi.lib")

CONST CHAR g_sz_CLASS_NAME[] = "Calc PV_319";

CONST INT g_i_INTERVAL = 5;
CONST INT g_i_BUTTON_SIZE = 50;
CONST INT g_i_BUTTON_DOUBLE_SIZE = g_i_BUTTON_SIZE * 2 + g_i_INTERVAL;

CONST INT g_i_FONT_HEIGHT = 32;
CONST INT g_i_FONT_WIDTH = g_i_FONT_HEIGHT * 2 / 5;
CONST INT g_i_DISPLAY_WIDTH = g_i_BUTTON_SIZE * 5 + g_i_INTERVAL * 4;
CONST INT g_i_DISPLAY_HEIGHT = g_i_FONT_HEIGHT + 2;

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

CONST COLORREF g_DISPLAY_BACKGROUND[] = { RGB(0, 0, 100), RGB(0,  50, 0) };
CONST COLORREF g_DISPLAY_FOREGROUND[] = { RGB(255, 0, 0), RGB(0, 255, 0) };
CONST COLORREF g_WINDOW_BACKGROUND[] = { RGB(0, 0, 150), RGB(75,  75, 75) };

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
VOID SetSkin(HWND hwnd, CONST CHAR* skin);
VOID SetSkinFromDLL(HWND hwnd, CONST CHAR* skin);
VOID GetExeDirectory(CHAR* buffer, DWORD size);

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
	HBITMAP hBackground = (HBITMAP)LoadImage(hInstance, "Picture\\wolf.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	wClass.hbrBackground = CreatePatternBrush(hBackground);

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

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static DOUBLE a = DBL_MIN;
	static DOUBLE b = DBL_MIN;
	static INT operation = 0;
	static BOOL input = FALSE;
	static BOOL input_operation = FALSE;
	//////////////////////////////////////

	static INT color_index = 0;
	static HANDLE hMyFont = NULL;

	//////////////////////////////////////

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
		//////////////////		FONT	 /////////////////
		AddFontResourceEx("Fonts\\Calculator.ttf", FR_PRIVATE, 0);
		//////////////////////////////////////////////////
		//https://stackoverflow.com/questions/58712918/win32-use-a-resource-font-inside-the-application
		CHAR filepath[MAX_PATH]{};
		GetExeDirectory(filepath, MAX_PATH);
		CHAR dllpath[MAX_PATH]{};
		PathCombine(dllpath, filepath, ("Fonts\\Terminator2.dll"));
		HINSTANCE hInstFont = LoadLibrary(dllpath);
		//HINSTANCE hInstFont = LoadLibrary("..\\Debug\\FontOnlyDLL.dll");
		HRSRC hFontRes = FindResource(hInstFont, MAKEINTRESOURCE(99), "BINARY");
		HGLOBAL hFntMem = LoadResource(hInstFont, hFontRes);
		VOID* fntData = LockResource(hFntMem);
		DWORD nFonts = 0;
		DWORD len = SizeofResource(hInstFont, hFontRes);
		hMyFont = AddFontMemResourceEx(fntData, len, nullptr, &nFonts);
		HFONT hFont = CreateFont
		(
			g_i_FONT_HEIGHT, g_i_FONT_WIDTH,
			0,	//Escapement - Наклон шрифта в десятках градусов
			0,  //Orientation - ???
			FW_BOLD,	//Weight - Толщина
			FALSE,	//Italic - Курсив
			FALSE,	//Underline - Подчеркнутый
			FALSE,	//Strikeout - Перечеркнутый
			ANSI_CHARSET,
			OUT_TT_PRECIS,
			CLIP_TT_ALWAYS,
			ANTIALIASED_QUALITY,
			FF_DONTCARE,
			"Terminator Two"
			//"Digital-7"
			//"Calculator"
		);
		//MoveTo WM_DESTROY: RemoveFontMemResourceEx(hMyFont);
		FreeLibrary(hInstFont);
		//////////////////////////////////////////////////
		SendMessage(hEdit, WM_SETFONT, (WPARAM)hFont, TRUE);

		//TODO:	Button Icons.
		CHAR sz_digit[2] = "0";
		for (int i = 6; i >= 0; i -= 3)
		{
			for (int j = 0; j < 3; j++)
			{
				sz_digit[0] = 49 + i + j;	//49 - ASCII-код единицы.
				CreateWindowEx
				(
					NULL, "Button", sz_digit,
					WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
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

		HWND hButton0 = CreateWindowEx
		(
			NULL, "Button", "0",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
			g_i_BUTTON_START_X,
			g_i_BUTTON_START_Y + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 3,
			g_i_BUTTON_DOUBLE_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_0,
			GetModuleHandle(NULL),
			NULL
		);

		HBITMAP hBitmap0 = (HBITMAP)LoadImage
		(
			GetModuleHandle(NULL),
			"ButtonsBMP\\square_blue\\button_0.bmp",
			IMAGE_BITMAP,
			g_i_BUTTON_DOUBLE_SIZE, g_i_BUTTON_SIZE,
			LR_LOADFROMFILE
		);
		SendMessage(hButton0, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap0);

		CreateWindowEx
		(
			NULL, "Button", ".",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
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
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
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
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
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
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
			g_i_CONTROL_BUTTON_START_X,
			g_i_CONTROL_BUTTON_START_Y + g_i_BUTTON_SIZE + g_i_INTERVAL,
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_CLR,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL, "Button", "=",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
			g_i_CONTROL_BUTTON_START_X,
			g_i_CONTROL_BUTTON_START_Y + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 2,
			g_i_BUTTON_SIZE, g_i_BUTTON_DOUBLE_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_EQUAL,
			GetModuleHandle(NULL),
			NULL
		);
		SetSkinFromDLL(hwnd, "square_blue");
	}
	break;
	case WM_CTLCOLOREDIT:
	{
		HDC hdc = (HDC)wParam;
		HWND hEdit = (HWND)lParam;
		if (GetDlgCtrlID(hEdit) == IDC_EDIT_DISPLAY)
		{
			//SetBkMode(hdc, OPAQUE);
			SetTextColor(hdc, g_DISPLAY_FOREGROUND[color_index]);
			SetBkColor(hdc, g_DISPLAY_BACKGROUND[color_index]);

			HBRUSH hbrBackground = CreateSolidBrush(g_WINDOW_BACKGROUND[color_index]);
			SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG)hbrBackground);
			SendMessage(hwnd, WM_ERASEBKGND, wParam, 0);
			return (LRESULT)hbrBackground;
		}
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
			//TODO: Если первый символ '.', то последующий ввод неправильный
			if (!input && !input_operation)
			{
				SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_CLR), 0);
				//ZeroMemory(sz_display, SIZE);
				sz_display[0] = 0;
			}
			if (!input && input_operation /*&& !strchr(sz_display, '.')*/)sz_display[0] = 0;

			sz_digit[0] = LOWORD(wParam) - IDC_BUTTON_0 + '0';
			if (strlen(sz_display) == 1 && sz_display[0] == '0')
				sz_display[0] = sz_digit[0];
			else
				strcat(sz_display, sz_digit);
			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);

			input = TRUE;
			//input_operation = FALSE;
		}
		if (LOWORD(wParam) == IDC_BUTTON_POINT)
		{
			if (strchr(sz_display, '.') && input)break;
			if (input_operation && a == atof(sz_display))strcpy(sz_display, "0.");
			else strcat(sz_display, ".");
			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
			input = TRUE;
			strcat(sz_display, ".");
		}
		//if (LOWORD(wParam) == IDC_EDIT_DISPLAY && HIWORD(wParam) == EN_SETFOCUS)SetFocus(hwnd);
		if (LOWORD(wParam) == IDC_BUTTON_BSP)
		{
			if (strlen(sz_display) == 1)sz_display[0] = '0';
			else sz_display[strlen(sz_display) - 1] = 0;
			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
		}
		if (LOWORD(wParam) == IDC_BUTTON_CLR)
		{
			a = b = DBL_MIN;
			operation = 0;
			input = FALSE;
			input_operation = FALSE;
			//strcpy(sz_display, "0");
			//sz_display[0] = 0;
			ZeroMemory(sz_display, SIZE);
			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)"0");
		}
		if (LOWORD(wParam) >= IDC_BUTTON_PLUS && LOWORD(wParam) <= IDC_BUTTON_SLASH)
		{
			//SendMessage(hEditDisplay, WM_GETTEXT, SIZE, (LPARAM)sz_display);
			if (a == DBL_MIN)a = atof(sz_display);
			//input = FALSE;
			if (input_operation)SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_EQUAL), 0);
			operation = LOWORD(wParam);
			input = FALSE;
			input_operation = TRUE;
		}

		if (LOWORD(wParam) == IDC_BUTTON_EQUAL)
		{
			//if(b==DBL_MIN && !input)
			if (input || b == DBL_MIN && !input)b = atof(sz_display);
			input = FALSE;
			switch (operation)
			{
			case IDC_BUTTON_PLUS:	a += b;	break;
			case IDC_BUTTON_MINUS:	a -= b;	break;
			case IDC_BUTTON_ASTER:	a *= b;	break;
			case IDC_BUTTON_SLASH:	a /= b;	break;
			}
			//input = FALSE;
			input_operation = FALSE;
			if (a == DBL_MIN)strcpy(sz_display, "0");
			else sprintf(sz_display, "%g", a);
			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
		}
		SetFocus(hwnd);
	}
	break;
	case WM_KEYDOWN:
	{
		if (GetKeyState(VK_SHIFT) < 0)
		{
			if (wParam == 0x38)
				SendMessage(GetDlgItem(hwnd, IDC_BUTTON_ASTER), BM_SETSTATE, TRUE, 0);
		}
		else if (wParam >= '0' && wParam <= '9')
		{
			SendMessage(GetDlgItem(hwnd, wParam - '0' + IDC_BUTTON_0), BM_SETSTATE, TRUE, 0);
		}
		else if (wParam >= 0x60 && wParam <= 0x69)
		{
			SendMessage(GetDlgItem(hwnd, wParam - 0x60 + IDC_BUTTON_0), BM_SETSTATE, TRUE, 0);
		}

		switch (wParam)
		{
		case VK_ADD:
		case VK_OEM_PLUS:
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_PLUS), BM_SETSTATE, TRUE, 0);
			break;
		case VK_SUBTRACT:
		case VK_OEM_MINUS:
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_MINUS), BM_SETSTATE, TRUE, 0);
			break;
		case VK_MULTIPLY:
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_ASTER), BM_SETSTATE, TRUE, 0);
			break;
		case VK_DIVIDE:
		case VK_OEM_2:
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_SLASH), BM_SETSTATE, TRUE, 0);
			break;
		case VK_DECIMAL:
		case VK_OEM_PERIOD:
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_POINT), BM_SETSTATE, TRUE, 0);
			break;
		case VK_BACK:
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_BSP), BM_SETSTATE, TRUE, 0);
			break;
		case VK_ESCAPE:
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_CLR), BM_SETSTATE, TRUE, 0);
			break;
		case VK_RETURN:
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_EQUAL), BM_SETSTATE, TRUE, 0);
			break;
		}
	}
	break;
	case WM_KEYUP:
	{
		//if (wParam >= 0x30 && wParam <= 0x39)
			//SendMessage(hwnd, WM_COMMAND, wParam - 0x30 + IDC_BUTTON_0, 0);
		if (GetKeyState(VK_SHIFT) < 0)
		{
			if (wParam == 0x38)
			{
				SendMessage(GetDlgItem(hwnd, IDC_BUTTON_ASTER), BM_SETSTATE, FALSE, 0);
				SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_ASTER, 0);
			}
		}
		else if (wParam >= '0' && wParam <= '9')
		{
			SendMessage(GetDlgItem(hwnd, wParam - '0' + IDC_BUTTON_0), BM_SETSTATE, FALSE, 0);
			SendMessage(hwnd, WM_COMMAND, wParam - '0' + IDC_BUTTON_0, 0);
		}
		else if (wParam >= 0x60 && wParam <= 0x69)
		{
			SendMessage(GetDlgItem(hwnd, wParam - 0x60 + IDC_BUTTON_0), BM_SETSTATE, FALSE, 0);
			SendMessage(hwnd, WM_COMMAND, wParam - 0x60 + IDC_BUTTON_0, 0);
		}

		switch (wParam)
		{
		case VK_ADD:
		case VK_OEM_PLUS:
			SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_PLUS), 0);
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_PLUS), BM_SETSTATE, FALSE, 0);
			break;
		case VK_SUBTRACT:
		case VK_OEM_MINUS:
			SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_MINUS), 0);
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_MINUS), BM_SETSTATE, FALSE, 0);
			break;
		case VK_MULTIPLY:
			SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_ASTER), 0);
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_ASTER), BM_SETSTATE, FALSE, 0);
			break;
		case VK_DIVIDE:
		case VK_OEM_2:
			SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_SLASH), 0);
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_SLASH), BM_SETSTATE, FALSE, 0);
			break;
		case VK_DECIMAL:
		case VK_OEM_PERIOD:
			SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_POINT), 0);
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_POINT), BM_SETSTATE, FALSE, 0);
			break;
		case VK_BACK:
			SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_BSP), 0);
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_BSP), BM_SETSTATE, FALSE, 0);
			break;
		case VK_ESCAPE:
			SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_CLR), 0);
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_CLR), BM_SETSTATE, FALSE, 0);
			break;
		case VK_RETURN:
			SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_EQUAL), 0);
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_EQUAL), BM_SETSTATE, FALSE, 0);
			break;
		}
	}
	break;
	case WM_CONTEXTMENU:
	{
		HMENU hSubmenuSkins = CreatePopupMenu();
		InsertMenu(hSubmenuSkins, 0, MF_BYPOSITION | MF_STRING, IDR_METAL_MISTRAL, "Metal Mistral");
		InsertMenu(hSubmenuSkins, 0, MF_BYPOSITION | MF_STRING, IDR_SQUARE_BLUE, "Square Blue");

		HMENU hMenu = CreatePopupMenu();
		InsertMenu(hMenu, 0, MF_BYPOSITION | MF_POPUP, (UINT_PTR)hSubmenuSkins, "Skins");
		InsertMenu(hMenu, 1, MF_BYPOSITION | MF_SEPARATOR, 0, 0);
		InsertMenu(hMenu, 2, MF_BYPOSITION | MF_STRING, IDR_EXIT, "Exit");
		BOOL skin_index = TrackPopupMenu(hMenu, TPM_LEFTALIGN | TPM_BOTTOMALIGN | TPM_RETURNCMD, LOWORD(lParam), HIWORD(lParam), 0, hwnd, 0);
		switch (skin_index)
		{
		case IDR_SQUARE_BLUE:	SetSkinFromDLL(hwnd, "square_blue");	break;
		case IDR_METAL_MISTRAL: SetSkinFromDLL(hwnd, "metal_mistral"); break;
		case IDR_EXIT:			DestroyWindow(hwnd);
		}
		DestroyMenu(hSubmenuSkins);
		DestroyMenu(hMenu);

		if (skin_index >= IDR_SQUARE_BLUE && skin_index <= IDR_METAL_MISTRAL)
		{
			color_index = skin_index - IDR_CONTEXT_MENU - 1;
			HWND hEditDisplay = GetDlgItem(hwnd, IDC_EDIT_DISPLAY);
			HDC hdcDisplay = GetDC(hEditDisplay);
			SendMessage(hwnd, WM_CTLCOLOREDIT, (WPARAM)hdcDisplay, (LPARAM)hEditDisplay);
			ReleaseDC(hEditDisplay, hdcDisplay);

			CHAR sz_buffer[MAX_PATH]{};
			SendMessage(hEditDisplay, WM_GETTEXT, MAX_PATH, (LPARAM)sz_buffer);
			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
	}
	break;
	////////////////////////////
	case WM_DESTROY:
	{
		RemoveFontMemResourceEx(hMyFont);
		HWND hEdit = GetDlgItem(hwnd, IDC_EDIT_DISPLAY);
		HDC hdc = GetDC(hEdit);
		ReleaseDC(hEdit, hdc);
		PostQuitMessage(0);
	}
	break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	default:	return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

CONST CHAR* g_BUTTON_FILENAME[] =
{
	"button_0",
	"button_1",
	"button_2",
	"button_3",
	"button_4",
	"button_5",
	"button_6",
	"button_7",
	"button_8",
	"button_9",
	"button_point",
	"button_plus"	,
	"button_minus",
	"button_aster",
	"button_slash",
	"button_bsp"	,
	"button_clr",
	"button_equal"
};

VOID SetSkin(HWND hwnd, CONST CHAR* skin)
{
	//CHAR sz_path[MAX_PATH]{};
	CHAR sz_filename[FILENAME_MAX]{};
	//CHAR sz_full_name[MAX_PATH]{};
	for (INT i = 0; i < 18; i++)
	{
		HWND hButton = GetDlgItem(hwnd, IDC_BUTTON_0 + i);
		sprintf(sz_filename, "ButtonsBMP\\%s\\%s.bmp", skin, g_BUTTON_FILENAME[i]);
		HBITMAP bmpButton = (HBITMAP)LoadImage
		(
			GetModuleHandle(NULL),
			sz_filename,
			IMAGE_BITMAP,
			i + IDC_BUTTON_0 == IDC_BUTTON_0 ? g_i_BUTTON_DOUBLE_SIZE : g_i_BUTTON_SIZE,
			i + IDC_BUTTON_0 == IDC_BUTTON_EQUAL ? g_i_BUTTON_DOUBLE_SIZE : g_i_BUTTON_SIZE,
			LR_LOADFROMFILE
		);
		std::cout << sz_filename << std::endl;
		SendMessage(hButton, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmpButton);
	}
}
VOID SetSkinFromDLL(HWND hwnd, CONST CHAR* skin)
{
	CHAR filepath[MAX_PATH]{};
	CHAR filename[MAX_PATH]{};
	GetExeDirectory(filepath, MAX_PATH);
	sprintf(filename, "%s\\ButtonsBMP\\%s", filepath, skin);
	HMODULE hInst = LoadLibrary(filename);
	for (int i = IDC_BUTTON_0; i <= IDC_BUTTON_EQUAL; i++)
	{
		HBITMAP buttonBMP = (HBITMAP)LoadImage
		(
			hInst,
			MAKEINTRESOURCE(i),
			IMAGE_BITMAP,
			i > IDC_BUTTON_0		? g_i_BUTTON_SIZE : g_i_BUTTON_DOUBLE_SIZE,
			i < IDC_BUTTON_EQUAL	? g_i_BUTTON_SIZE : g_i_BUTTON_DOUBLE_SIZE,
			NULL
		);
		SendMessage(GetDlgItem(hwnd, i), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)buttonBMP);
	}
	FreeLibrary(hInst);
}
VOID GetExeDirectory(CHAR* buffer, DWORD size)
{
	GetModuleFileName(NULL, buffer, size);
	PathRemoveFileSpec(buffer);
}