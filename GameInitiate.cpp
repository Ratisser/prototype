#include <stdio.h>

#include "stdafx.h"
#include "Game.h"
#include "Vector2.h"
#pragma warning(disable:4996)
#pragma comment(lib, "msimg32.lib")


//-----------------------------------------------
// 장면이 시작되기 전 초기화 작업을 합니다.
// 추가 초기화 작업은 SceneUpdate에서 합니다.
//-----------------------------------------------
void Game::SceneInit()
{
	// 이미지 DC들의 메모리 할당
	mhMarineDC = new HDC[Marine::GetAllImageCount()];
	mhZerglingDC = new HDC[Zergling::GetAllImageCount()];
	mhUltraDC = new HDC[Ultra::GetAllImageCount()];
	mhSaraDC = new HDC[Sara::GetAllImageCount()];

	mGameState = GAME_INIT;
}


Game::Game()
{
	mCurrentTime = GetTickCount();
	mOldTime = mCurrentTime;
}


Game::~Game()
{
}

void Game::ErrorFileLoad() {
	SendMessage(Game::GetInstance()->hList, LB_INSERTSTRING, 0, (LPARAM)L"ERROR!!!");
	MessageBox(mhWnd, L"파일이 없습니다!!", mFileName, MB_OK);
	PostMessage(mhWnd, WM_DESTROY, NULL, NULL);
}

HDC Game::CreateBitmapDC(LPCWSTR filename)
{
	HBITMAP hBitmap;
	HDC hdc = GetDC(mhWnd);
	HDC hMemDC = CreateCompatibleDC(hdc);
	if ((hBitmap = (HBITMAP)LoadImage(NULL, filename, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE)) == NULL) {
		return NULL;
	}
	SelectObject(hMemDC, hBitmap);

	DeleteObject(hBitmap);
	ReleaseDC(mhWnd, hdc);
	return hMemDC;
}

HDC Game::CreateReverseDC(LPCWSTR filename)
{
	HBITMAP hBitmap, hReverseBit;
	HDC hdc = GetDC(mhWnd);
	HDC hReverseDC = CreateCompatibleDC(hdc);
	HDC hMemDC = CreateCompatibleDC(hReverseDC);

	if ((hBitmap = (HBITMAP)LoadImage(NULL, filename, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE)) == NULL) {
		return NULL;
	}
	BITMAP bit;
	GetObject(hBitmap, sizeof(BITMAP), &bit);

	SelectObject(hMemDC, hBitmap);

	hReverseBit = CreateCompatibleBitmap(hdc, bit.bmWidth, bit.bmHeight);
	SelectObject(hReverseDC, hReverseBit);

	StretchBlt(hReverseDC, bit.bmWidth, 0, -bit.bmWidth, bit.bmHeight, hMemDC, 0, 0, bit.bmWidth, bit.bmHeight, SRCCOPY);


	DeleteObject(hBitmap);
	DeleteObject(hReverseBit);
	ReleaseDC(mhWnd, hdc);
	return hReverseDC;
}


void Game::ClearSelectedUnit() {
	for (int i = 0; i < 12; i++) {
		mSelectedUnit[i] = nullptr;
	}
}

void Game::SceneRelease() {
	for (int i = 0; i < Zergling::GetAllImageCount();i++) {
		DeleteDC(mhZerglingDC[i]);
	}
	for (int i = 0; i < Marine::GetAllImageCount(); i++) {
		DeleteDC(mhMarineDC[i]);
	}
	for (int i = 0; i < Ultra::GetAllImageCount();i++) {
		DeleteDC(mhUltraDC[i]);
	}
	for (int i = 0; i < Sara::GetAllImageCount();i++) {
		DeleteDC(mhSaraDC[i]);
	}
	delete[] mhZerglingDC;
	delete[] mhMarineDC;
	delete[] mhUltraDC;
	delete[] mhSaraDC;
	Unit::Release();
}