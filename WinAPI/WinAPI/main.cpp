#include<Windows.h>

//#define MESSAGE_BOX

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{

#ifdef MESSAGE_BOX
	MessageBox
	(
		NULL,
		"Hello WinAPI!\nЭто MessageBox, детка.",
		"Заголовок окна",
		MB_YESNO | MB_ICONQUESTION
		| MB_HELP
		| MB_DEFBUTTON4
		| MB_SYSTEMMODAL
	);
#endif // MESSAGE_BOX

	return 0;
}