#include "stdafx.h"
#include "GameFramework.h"

void GameFramework::fullScreenModeChange()
{
	DEVMODE sDevMode;
	sDevMode.dmSize = sizeof(DEVMODE);
	sDevMode.dmPelsWidth = CLIENT_WIDTH;
	sDevMode.dmPelsHeight = CLIENT_HEIGHT;
	sDevMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;
	ChangeDisplaySettings(&sDevMode, CDS_FULLSCREEN);
}

void GameFramework::ChangeScreenMode(BOOL bIsFullMode)
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

void GameFramework::Init(HINSTANCE hInst, HWND hWnd) {
	HDC hdc;
	HBITMAP hBit;

	QueryPerformanceFrequency(&mFrequency);
	QueryPerformanceCounter(&mOldTime);
	QueryPerformanceCounter(&mOldRenderTime);
	mdwOldTime = GetTickCount();

	mhInst = hInst;
	mhWnd = hWnd;
	hdc = GetDC(mhWnd);
	hBit = CreateCompatibleBitmap(hdc, CLIENT_WIDTH, CLIENT_HEIGHT);
	mhBackBuffer = CreateCompatibleDC(hdc);
	HBRUSH brush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(15, 230, 15));
	SelectObject(mhBackBuffer, brush);
	SelectObject(mhBackBuffer, pen);
	SelectObject(mhBackBuffer, hBit);
	DeleteObject(hBit);


	AdjustWindowRect(&mClientRect, WS_OVERLAPPEDWINDOW, TRUE);
	//FillRect(mhBackBuffer, &mClientRect, (HBRUSH)GetStockObject(BLACK_BRUSH));

	ReleaseDC(mhWnd, hdc);

	ChangeScreenMode(0);

	SceneInit();

}

void GameFramework::Update() {
	SceneUpdate();
}

void GameFramework::Render() {
	mdwCurrentTime = GetTickCount();
	QueryPerformanceCounter(&mCurTime);
	QueryPerformanceCounter(&mCurRenderTime);
	mElapsedTime.QuadPart = mCurTime.QuadPart - mOldTime.QuadPart;
	mDeltaTime = mElapsedTime.QuadPart / (float)mFrequency.QuadPart;

	if (mDeltaTime > 0.016666666) {
		mOldTime = mCurTime;
		if (mdwCurrentTime - mdwOldTime >= 1000)
		{
			mdwOldTime = mdwCurrentTime;
			mnFPS = mnFPSCount;
			mnFPSCount = 0;
		}
		HDC hdc = GetDC(mhWnd);

		PatBlt(mhBackBuffer, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT, BLACKNESS);

		SceneRender();
		if (mDrag) {
			Rectangle(mhBackBuffer, mMouseSP.x, mMouseSP.y, mMouseEP.x, mMouseEP.y);
		}

		BitBlt(hdc, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT, mhBackBuffer, 0, 0, SRCCOPY);

		ReleaseDC(mhWnd, hdc);
		mnFPSCount++;
	}
}

void GameFramework::MouseProcess(UINT msg, LPARAM lParam) {
	switch (msg)
	{
	case WM_LBUTTONDOWN:
		mMouseState = LBUTTONDOWN;
		mMousePoint.x = mMouseSP.x = mMouseEP.x = LOWORD(lParam);
		mMousePoint.y = mMouseSP.y = mMouseEP.y = HIWORD(lParam);
		mDrag = 1;
		break;

	case WM_LBUTTONUP:
		mMouseState = LBUTTONUP;
		mMousePoint.x = mMouseEP.x = LOWORD(lParam);
		mMousePoint.y = mMouseEP.y = HIWORD(lParam);
		mDragRect.left = (LONG)(mMouseSP.x < mMouseEP.x ? mMouseSP.x : mMouseEP.x);
		mDragRect.right = (LONG)(mMouseSP.x > mMouseEP.x ? mMouseSP.x : mMouseEP.x);
		mDragRect.top= (LONG)(mMouseSP.y < mMouseEP.y ? mMouseSP.y : mMouseEP.y);
		mDragRect.bottom = (LONG)(mMouseSP.y > mMouseEP.y ? mMouseSP.y : mMouseEP.y);
		mDrag = 0;
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
		if (mDrag)
		{
			mMouseEP.x = LOWORD(lParam);
			mMouseEP.y = HIWORD(lParam);
		}
		break;
	default:
		mMouseState = MOUSE_NONE;
		break;
		// asd
	}
}

void GameFramework::Release() {

	SceneRelease();

}
