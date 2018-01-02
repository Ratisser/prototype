#include <stdio.h>

#include "stdafx.h"
#include "Game.h"
#include "Vector2.h"
#pragma warning(disable:4996)
#pragma comment(lib, "msimg32.lib")

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
	MessageBox(mhWnd, L"������ �����ϴ�!!", mFileName, MB_OK);
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

//-----------------------------------------------
// ����� ���۵Ǳ� �� �ʱ�ȭ �۾��� �մϴ�.
// �߰� �ʱ�ȭ �۾��� SceneUpdate���� �մϴ�.
//-----------------------------------------------
void Game::SceneInit()
{
	// �̹��� DC���� �޸� �Ҵ�
	mhMarineDC = new HDC[Marine::GetAllImageCount()];
	mhZerglingDC = new HDC[Zergling::GetAllImageCount()];
	mhUltraDC = new HDC[Ultra::GetAllImageCount()];
	mhSaraDC = new HDC[Sara::GetAllImageCount()];

	mGameState = GAME_INIT;
}
//-----------------------------------------------
// ���ӿ� �ʿ��� ������ ������Ʈ �մϴ�.
//-----------------------------------------------
void Game::SceneUpdate() {
	mCurrentTime = GetTickCount();

	switch (mGameState) {
	case GAME_INIT:
	{
		mOldTime = mCurrentTime;
		mSelectedCount = 0;

		// �� ī��Ʈ�� �̹����� �ݴ�� �׸��� ���� ���� 17���� �ʱ�ȭ
		// �� �׷����� �𸣰����� �׸��� 17������ �����ϰ� ¥��������...(A*�˰��� ���� �̵��� 8���⿡�� Ȯ��� 16�������� ����)
		int ImageCount = 0;

		//-----------------------------------
		// ��� �̹��� �ε�
		//-----------------------------------
		wsprintf(mSystemMsg, L"��� �ε���...");
		SceneRender();
		wsprintf(mFileName, L"map\\map_01.bmp");
		if ((mhBackgroundDC = CreateBitmapDC(mFileName)) == NULL) {
			ErrorFileLoad();
			return;
		}

		//-----------------------------------------
		// ���� �̹��� ���� �ε�
		//-----------------------------------------

		// ���� �ε�
		for (int i = 0; i < Marine::GetAllImageCount(); i++) {
			wsprintf(mSystemMsg, L"���� �ε���...(%d/%d)", i + 1, Marine::GetAllImageCount());
			wsprintf(mFileName, L"unit\\marine\\img%d.bmp", i + 1);
			Render();
			if (ImageCount % 2 == 1 && i < Marine::GetUnitImageCount()) {
				if ((mhMarineDC[i] = CreateReverseDC(mFileName)) == NULL) {
					ErrorFileLoad();
					return;
				}
			}
			else {
				if ((mhMarineDC[i] = CreateBitmapDC(mFileName)) == NULL) {
					ErrorFileLoad();
					return;
				}
			}

			ImageCount = (ImageCount + 1) % 17;
		}
		ImageCount = 0;
		// ���۸� �ε�
		for (int i = 0; i < Zergling::GetAllImageCount(); i++) {
			wsprintf(mSystemMsg, L"���� �ε���...(%d/%d)", i + 1, Zergling::GetAllImageCount());
			wsprintf(mFileName, L"unit\\zergling\\img%d.bmp", i + 1);
			Render();
			if (ImageCount % 2 == 1 && i < Zergling::GetUnitImageCount()) {
				if ((mhZerglingDC[i] = CreateReverseDC(mFileName)) == NULL) {
					ErrorFileLoad();
					return;
				}
			}
			else {
				if ((mhZerglingDC[i] = CreateBitmapDC(mFileName)) == NULL) {
					ErrorFileLoad();
					return;
				}
			}

			ImageCount = (ImageCount + 1) % 17;
		}
		ImageCount = 0;
		// ��Ʈ�󸮽�ũ �ε�
		for (int i = 0; i < Ultra::GetAllImageCount(); i++) {
			wsprintf(mSystemMsg, L"���� �ε���...(%d/%d)", i + 1, Ultra::GetAllImageCount());
			wsprintf(mFileName, L"unit\\ultra\\img%d.bmp", i + 1);
			Render();
			if (ImageCount % 2 == 1 && i < Ultra::GetUnitImageCount()) {
				if ((mhUltraDC[i] = CreateReverseDC(mFileName)) == NULL) {
					ErrorFileLoad();
					return;
				}
			}
			else {
				if ((mhUltraDC[i] = CreateBitmapDC(mFileName)) == NULL) {
					ErrorFileLoad();
					return;
				}
			}

			ImageCount = (ImageCount + 1) % 17;
		}
		ImageCount = 0;
		// sara
		for (int i = 0; i < Sara::GetAllImageCount(); i++) {
			wsprintf(mSystemMsg, L"���� �ε���...(%d/%d)", i + 1, Sara::GetAllImageCount());
			wsprintf(mFileName, L"unit\\sara\\img%d.bmp", i + 1);
			Render();
			if (ImageCount % 2 == 1 && i < Sara::GetUnitImageCount()) {
				if ((mhSaraDC[i] = CreateReverseDC(mFileName)) == NULL) {
					ErrorFileLoad();
					return;
				}
			}
			else {
				if ((mhSaraDC[i] = CreateBitmapDC(mFileName)) == NULL) {
					ErrorFileLoad();
					return;
				}
			}

			ImageCount = (ImageCount + 1) % 17;
		}

		//for (int i = 0; i < MAX_UNIT_COUNT; i++) {
		//	mMousePoint.x = 100+(i%100)*5;
		//	mMousePoint.y = 100+(i/100)*10;
		//	Unit::AddUnit(ULTRA);
		//}
		mCurrentTime = GetTickCount();
		wsprintf(mSystemMsg, L"�ε��� �ɸ� �ð� : %d ms", mCurrentTime - mOldTime);
		Render();
		wsprintf(mSystemMsg, L"�ε� �Ϸ�!");
		Render();
		mOldTime = mCurrentTime;
		mGameState = GAME_TITLE;
		break;
	}
	case GAME_TITLE:

		mGameState = GAME_ROOP;
		break;
		//================================================
		// Game Roop
		//================================================
	case GAME_ROOP:
	{
		mOldTime = mCurrentTime;
		Unit** pUnit;
		VECTOR2 *point;

		// ������ �ൿ ����
		if (Unit::GetUnitCount() > 0) {
			pUnit = Unit::GetUnitList();
			for (int i = 0; i < Unit::GetUnitCount(); i++) {
				(*pUnit)->UnitProcess();
				*pUnit++;
			}
		}

		// ������ ����
		if (mMouseState == LBUTTONUP) {
			if (Unit::GetUnitCount() > 0) {
				// �巡�� ����
				mSelectedCount = 0;
				int unitSize;
				pUnit = Unit::GetUnitList();
				for (int i = 0; i < Unit::GetUnitCount(); i++) {
					if (mSelectedCount >= 12) break;
					point = (*pUnit)->GetPos();
					unitSize = (*pUnit)->GetUnitSize();
					if ((point->x > mDragRect.left && point->x < mDragRect.right && point->y > mDragRect.top && point->y < mDragRect.bottom)
						|| Vec2Dist(&mMouseEP, point) < unitSize*unitSize) {
						if (mSelectedCount == 0) {
							for (int i = 0; i < 12; i++) {
								mSelectedUnit[i] = nullptr;
							}
						}
						mSelectedUnit[mSelectedCount] = *pUnit;
						mSelectedCount++;
					}
					*pUnit++;
				}
			}
			int count = 0;
			for (int i = 0; i < 12; i++) {
				if (mSelectedUnit[i] != nullptr) count++;
			}
			mSelectedCount = count;
		}

		// ���� �̵����
		if (mMouseState == RBUTTONDOWN) {
			pUnit = mSelectedUnit;
			for (int i = 0; i < 12; i++) {
				if (*pUnit == nullptr) {
					break;
				}
				else {
					(*pUnit)->SetTargetVector(&mMousePoint);
					(*pUnit)->Move();
				}
				*pUnit++;
			}
		}

		break;
	}
	case GAME_DESTROY:

		break;
	}
}
//-----------------------------------------------
// ���� ȭ�鿡 ���̴� ����� ó���մϴ�
//-----------------------------------------------
void Game::SceneRender() {
	switch (mGameState) {
	case GAME_INIT:
	{
		TextOut(mhBackBuffer, CLIENT_WIDTH / 2 - 100, CLIENT_HEIGHT / 2, mSystemMsg, wcslen(mSystemMsg));
		SendMessage(hList, LB_INSERTSTRING, 0, (LPARAM)mSystemMsg);
	}
	break;
	case GAME_TITLE:

		break;
	case GAME_ROOP:
	{
		Unit** pUnit;
		VECTOR2 *point;
		Image *ImgInfo;
		int halfWidth;
		int halfHeight;

		// ��� �׸���
		BitBlt(mhBackBuffer, 0, 0, 800, 600, mhBackgroundDC, 0, 0, SRCCOPY);

		//------------------------------
		// ���õ� ���� �� �׸���
		//------------------------------
		if (mSelectedCount != 0) {
			for (int i = 0; i < 12; i++)
				if (mSelectedUnit[i] == nullptr) break;
				else {
					point = mSelectedUnit[i]->GetPos();
					ImgInfo = mSelectedUnit[i]->GetImgInfo();
					int unitSize = mSelectedUnit[i]->GetUnitSize()/2;
					Ellipse(mhBackBuffer, point->x - unitSize-5, point->y + unitSize, point->x + unitSize+5, point->y + unitSize + 10);
					
				}

		}


		//------------------------------
		// ���� �׸���
		//------------------------------
		pUnit = Unit::GetUnitList();
		for (int i = 0; i < Unit::GetUnitCount(); i++) {
			point = (*pUnit)->GetPos();
			ImgInfo = (*pUnit)->GetImgInfo();
			halfWidth = ImgInfo->bitWidth / 2;
			halfHeight = ImgInfo->bitHeight / 2;
			HDC *hImageArray;

			switch ((*pUnit)->GetUnitID())
			{
			case MARINE:
				hImageArray = mhMarineDC;
				break;
			case ZERGLING:
				hImageArray = mhZerglingDC;
				break;
			case ULTRA:
				hImageArray = mhUltraDC;
				break;
			case SARA:
				hImageArray = mhSaraDC;
				break;
			}
			int render = (*pUnit)->GetRenderTarget();
			TransparentBlt(mhBackBuffer, point->x - halfWidth, point->y - halfHeight, ImgInfo->bitWidth, ImgInfo->bitHeight, hImageArray[render], 0, 0, ImgInfo->bitWidth, ImgInfo->bitHeight, ImgInfo->transColor);
			*pUnit++; // �����ͷ� Ž����
		}

		SetBkColor(mhBackBuffer, RGB(0, 0, 0));
		SetTextColor(mhBackBuffer, RGB(255, 255, 255));
		_stprintf(mFPS, _T("FPS:%-4d"), mnFPS);
		TextOut(mhBackBuffer, 0, 0, mFPS, _tcslen(mFPS));

		_stprintf(mUnitCount, _T("UnitCount:%-4d, mX: %-4.2f, mY: %-4.2f"), Unit::GetUnitCount(), mMousePoint.x, mMousePoint.y);
		TextOut(mhBackBuffer, 0, 20, mUnitCount, _tcslen(mUnitCount));

		_stprintf(mSystemMsg, _T("�������� ���� : %d"), mSelectedCount);
		TextOut(mhBackBuffer, 0, 40, mSystemMsg, _tcslen(mSystemMsg));

		break;
	}
	case GAME_DESTROY:

		break;
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