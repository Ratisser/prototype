#include "stdafx.h"
#include "GameFrame.h"

void GameFrame::fullScreenModeChange()
{
	DEVMODE sDevMode;
	sDevMode.dmSize = sizeof(DEVMODE);
	sDevMode.dmPelsWidth = CLIENT_WIDTH;
	sDevMode.dmPelsHeight = CLIENT_HEIGHT;
	sDevMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;
	ChangeDisplaySettings(&sDevMode, CDS_FULLSCREEN);
}

void GameFrame::ChangeScreenMode(BOOL bIsFullMode)
{
	RECT rect;
	mbFullScreen = bIsFullMode;
	if (bIsFullMode)
	{
		SetWindowLong(mhWnd, GWL_STYLE, WS_POPUP);
		SetWindowPos(mhWnd, 0, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT, SWP_SHOWWINDOW);
		fullScreenModeChange();
	}
	else {
		ChangeDisplaySettings(NULL, 0);
		SetWindowLong(mhWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);

		// 윈도우 크기 설정
		SetRect(&rect, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT);
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
		SetWindowPos(mhWnd, 0, 100, 100, rect.right - rect.left, rect.bottom - rect.top, SWP_SHOWWINDOW);
	}
}

void GameFrame::Init(HWND hWnd) {
	HDC hdc;
	HBITMAP hBit;

	mhWnd = hWnd;
	hdc = GetDC(mhWnd);
	hBit = CreateCompatibleBitmap(hdc, CLIENT_WIDTH, CLIENT_HEIGHT);
	mhBackBuffer = CreateCompatibleDC(hdc);
	SelectObject(mhBackBuffer,hBit);
	DeleteObject(hBit);


	AdjustWindowRect(&mClientRect, WS_OVERLAPPEDWINDOW, TRUE);
	//FillRect(mhBackBuffer, &mClientRect, (HBRUSH)GetStockObject(BLACK_BRUSH));

	ReleaseDC(mhWnd, hdc);

	ChangeScreenMode(0);

	mdwOldTime = GetTickCount();
	mdwOldRenderTime = GetTickCount();
	SceneInit();

}

void GameFrame::Update() {
	SceneUpdate();
}

void GameFrame::Render() {
	mdwCurrentTime = GetTickCount();
	mdwCurRenderTime = GetTickCount();
	if (mdwCurrentTime - mdwOldTime >= 1000)
	{
		mdwOldTime = mdwCurrentTime;
		mnFPS = mnFPSCount;
		mnFPSCount = 0;
	}
	else {
		HDC hdc = GetDC(mhWnd);

		PatBlt(mhBackBuffer, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT, BLACKNESS);

		SceneRender();

		BitBlt(hdc, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT, mhBackBuffer, 0, 0, SRCCOPY);

		ReleaseDC(mhWnd, hdc);
		mdwOldRenderTime = mdwCurRenderTime;
		mnFPSCount++;
	}
}

void GameFrame::MouseProcess(UINT msg, LPARAM lParam) {
	switch (msg)
	{
	case WM_LBUTTONDOWN:
		mMouseState = LBUTTONDOWN;
		mMousePoint.x = LOWORD(lParam);
		mMousePoint.y = HIWORD(lParam);
		break;

	case WM_LBUTTONUP:
		mMouseState = LBUTTONUP;
		mMousePoint.x = LOWORD(lParam);
		mMousePoint.y = HIWORD(lParam);
		break;
	case WM_RBUTTONDOWN:
		mMouseState = RBUTTONDOWN;
		mMousePoint.x = LOWORD(lParam);
		mMousePoint.y = HIWORD(lParam);
		break;
	case WM_RBUTTONUP:
		mMouseState = RBUTTONUP;
		mMousePoint.x = LOWORD(lParam);
		mMousePoint.y = HIWORD(lParam);
		break;
	case WM_MOUSEMOVE:
		break;
	default:
		mMouseState = MOUSE_NONE;
		break;
	}
}

void GameFrame::Release() {

	SceneRelease();

}
