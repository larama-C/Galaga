#include <windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass = TEXT("√÷∫¥¡ÿ");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
	, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPED | WS_SYSMENU,
		720, 100, 500, 700,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

HBITMAP BitMap;

void drawing_img(HDC hdc, int x, int y, int bitmapNumber)
{
	HBITMAP NewBitMap, OldBitMap;

	HDC MemDC = CreateCompatibleDC(hdc);
	NewBitMap = LoadBitmap(g_hInst, MAKEINTRESOURCE(bitmapNumber));
	OldBitMap = (HBITMAP)SelectObject(MemDC, NewBitMap);
	BitBlt(hdc, x, y, 100, 100, MemDC, 0, 0, SRCCOPY);

	SelectObject(MemDC, OldBitMap);
	DeleteObject(NewBitMap);
}

void Render()
{
	if (BitMap) DeleteObject(BitMap);

	HBITMAP OldBitmap;

	HDC whdc = GetDC(hWndMain);


}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage) {
	case WM_CREATE:
		break;

	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		drawing_img(hdc, 100, 100, 3);
		EndPaint(hWnd, &ps);
		break;
	}

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
