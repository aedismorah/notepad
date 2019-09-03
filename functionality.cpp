#include <windows.h>
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		case WM_CREATE:
			CreateWindow("EDIT", "",WS_CHILD|WS_VISIBLE|WS_HSCROLL|WS_VSCROLL|ES_MULTILINE|ES_WANTRETURN,CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,hwnd, (HMENU)IDC_MAIN_TEXT, GetModuleHandle(NULL), NULL);
			SendDlgItemMessage(hwnd, IDC_MAIN_TEXT, WM_SETFONT,(WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE,0));
			break;
		case WM_SIZE:
			if(wParam != SIZE_MINIMIZED)
				MoveWindow(GetDlgItem(hwnd, IDC_MAIN_TEXT), 0, 0, LOWORD(lParam),HIWORD(lParam), TRUE);
			break;
		case WM_SETFOCUS:
			SetFocus(GetDlgItem(hwnd, IDC_MAIN_TEXT));
			break;
		case WM_COMMAND:
			switch(LOWORD(wParam)) {
				case CM_FILE_OPEN:
					DoFileOpenSave(hwnd, FALSE);
					break;
				case CM_FILE_SAVEAS:
					DoFileOpenSave(hwnd, TRUE);
					break;
				case CM_FILE_EXIT:
					PostMessage(hwnd, WM_CLOSE, 0, 0);
					break;
				case CM_ABOUT:
					MessageBox (NULL, "File Editor for Windows!\nCreated using the Win32 API" , "About...", 0);
					break;
			}
			break;
		case WM_CLOSE:
			DestroyWindow(hwnd);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}
