#include<Windows.h>
#include"resource.h"

CONST CHAR g_sz_LOGIN_INVITATION[] = "Введите имя пользователя";

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	/*
	------------------------------------
	hInstance - экземпляр загруженного *.exe-файла нашей программы.
	hPrevInst - предыдущий запущенный экземпляр. Этот параметр уже не используется,
				и оставлен только для совместимости.
	lpCmdLine - командная строка, с которой запустилась программа.
				Содержит имя имполняемого файла, и параметры запуска,
				например, имя отрываемого файла, URL Интернет-ресурса и т.д.
				Drag'n Drop так же работает через командную строку.
	LPSTR - Long Pointer to String
	nCmdShow  - Состояние окна при запуске, развернуто на весь экран, свернуто в окно,
				свернуто на панель задач.....
	------------------------------------
	*/
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	/*
	----------------------------
	hwnd (Handler to Windows) - дескриптор окна, это число, через которое к нему можно обратиться.
	----------------------------
	uMsg (Unsigned Message)   - сообщение, которое отправляется в окно.
	----------------------------
	wParam, lParam - параметры сообщения, зависят от сообщения, которое отправляется в окно.
	DWORD (DOUBLE WORD) - двойное слово (4 Байта = 32 бита);
	----------------------------
	*/
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);

		HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
		SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)g_sz_LOGIN_INVITATION);
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_EDIT_LOGIN:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE]{};
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			if (HIWORD(wParam) == EN_SETFOCUS && strcmp(sz_buffer, g_sz_LOGIN_INVITATION) == 0)
				SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)"");
			//strcmp(str1, str2);	//	String Compare
			//https://legacy.cplusplus.com/reference/cstring/strcmp/
			if (HIWORD(wParam) == EN_KILLFOCUS && strcmp(sz_buffer, "") == 0)
				SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)g_sz_LOGIN_INVITATION);
		}
		break;
		case IDC_BUTTON_COPY:
		{
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
			//Фкнкция GetDlgItem() возвращает HWND дочернего элемента окна по его ResourceID.
			//HWND - Handler to Window (Дескриптор окна) - это число, при помощи которого можно обратиться к окну.
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			SendMessage(hEditPassword, WM_SETTEXT, 0, (LPARAM)sz_buffer);
			SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_buffer);
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_COPY), WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
		break;
		case IDOK:		MessageBox(hwnd, "Была нажата кнопка OK!", "Info", MB_OK | MB_ICONINFORMATION); break;
		case IDCANCEL:	EndDialog(hwnd, 0); break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
		break;
	}
	return FALSE;
}