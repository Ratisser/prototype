#include "stdafx.h"
#include "Game.h"

//----------------------------------------------------
// 이 부모 인스턴스의 배열번호는 UnitID의 번호와 같아야함.
// 
//----------------------------------------------------
Unit *Game::mpParents[MAX_UNIT_SPECIES] = { new Marine, new Zergling, new Ultra, new Ghost };

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

HBITMAP Game::CreateBitmapDC(LPCWSTR filename)
{
	HBITMAP hBitmap;
	if ((hBitmap = (HBITMAP)LoadImage(NULL, filename, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE)) == NULL) {
		return NULL;
	}
	return hBitmap;
}

HBITMAP Game::CreateReverseDC(LPCWSTR filename)
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
	DeleteDC(hMemDC);
	DeleteDC(hReverseDC);
	ReleaseDC(mhWnd, hdc);
	return hReverseBit;
}


void Game::ClearSelectedUnit() {
	for (int i = 0; i < 12; i++) {
		mSelectedUnit[i] = nullptr;
	}
	mSelectedUnitCount = 0;
}
