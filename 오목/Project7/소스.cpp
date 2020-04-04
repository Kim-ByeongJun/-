#include <windows.h>


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass = TEXT("김병준_2013032023");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
	, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 1200, 1200,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0)) {
		TranslateMessage(&Message);	// 키보드 입력 메세지를 가공
		DispatchMessage(&Message);	// 메세지를 윈도우의 메세지 처리 함수
	}
	return (int)Message.wParam;              // 탈출 코드. 프로그램 종료
}

#define BSIZE 40
#define BSIZE2 80

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	int i, j;
	static int rect[14][14];
	static int x, y;
	HBRUSH hBrush, oldBrush;

	switch (iMessage) {

	case WM_CREATE:
		x = -50;  y = -50;
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		for (i = 0; i < 14; i++)			//바둑판 칸 생성
			for (j = 0; j < 14; j++)
			{
				Rectangle(hdc, i*BSIZE2, j*BSIZE2, (i + 1)*BSIZE2, (j + 1)*BSIZE2);
				if (rect[i][j] == 1)
					Ellipse(hdc, i*BSIZE2, j*BSIZE2, (i + 1)*BSIZE2, (j + 1)*BSIZE2);
				else if (rect[i][j] == 2)
				{
					hBrush = CreateSolidBrush(RGB(0, 0, 0));
					oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
					Ellipse(hdc, i*BSIZE2, j*BSIZE2, (i + 1)*BSIZE2, (j + 1)*BSIZE2);
					SelectObject(hdc, oldBrush);
					DeleteObject(hBrush);
				}
			}
		EndPaint(hWnd, &ps);
		break;

	case WM_LBUTTONDOWN:
		x = LOWORD(lParam) / BSIZE2; //영역 체크부분
		y = HIWORD(lParam) / BSIZE2;
		if (x < 14 && y < 14)
			rect[x][y] = 1;
		InvalidateRgn(hWnd, NULL, FALSE);
		break;

	case WM_RBUTTONDOWN:
		x = LOWORD(lParam) / BSIZE2; //영역 체크부분
		y = HIWORD(lParam) / BSIZE2;
		if (x < 14 && y < 14)
			rect[x][y] = 2;
		InvalidateRgn(hWnd, NULL, FALSE);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}