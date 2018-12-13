#include "stdafx.h"
#include "Game.h"

//----------------------------------------------------
// �� �θ� �ν��Ͻ��� �迭��ȣ�� UnitID�� ��ȣ�� ���ƾ���.
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
	MessageBox(mhWnd, L"������ �����ϴ�!!", mFileName, MB_OK);
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


//-----------------------------------------------
// ����� ���۵Ǳ� �� �ʱ�ȭ �۾��� �մϴ�.
// �߰� �ʱ�ȭ �۾��� SceneUpdate���� �մϴ�.
//-----------------------------------------------
void Game::SceneInit()
{
	// �̹��� DC���� �޸� �Ҵ�
	//mhMarineBit =	new	HBITMAP[mParents[0]->GetAllImageCount()];
	//mhZerglingBit =	new	HBITMAP[mParents[1]->GetAllImageCount()];
	//mhUltraBit =	new	HBITMAP[mParents[2]->GetAllImageCount()];
	//mhSaraBit =		new	HBITMAP[mParents[3]->GetAllImageCount()];
	mhBit = new HBITMAP*[MAX_UNIT_SPECIES];
	//for (int i = 0; i < MAX_UNIT_SPECIES; i++) {
	//	*(mhBit + i) = nullptr;
	//}
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
		mSelectedUnitCount = 0;
		int imageCount = 0;

		//-----------------------------------
		// ��� �̹��� �ε�
		//-----------------------------------
		wsprintf(mFileName, L"map\\map_01.bmp");
		if ((mhBackgroundBit = CreateBitmapDC(mFileName)) == NULL) {
			ErrorFileLoad();
			return;
		}

		//-----------------------------------------
		// ���� �̹��� ���� �ε�
		//-----------------------------------------

		for (int i = 0; i < MAX_UNIT_SPECIES; i++) {
			int sprCount = mpParents[i]->GetUnitImageCount();
			int allSprCount = mpParents[i]->GetAllImageCount();
			wsprintf(mFileName, L".");
			LoadString(mhInst, mpParents[i]->GetFilePath(), mFilePath, 50);
			*(mhBit + i) = new HBITMAP[allSprCount];
			for (int index = 0; index < allSprCount; index++) {
				*(*(mhBit + i) + index) = nullptr;
			}
			for (int j = 0; j < allSprCount; j++) {
				wsprintf(mFileName, L"%simg%d.bmp", mFilePath, j + 1);
				if (imageCount % 2 == 1 && j < sprCount) {
					if ((*(*(mhBit + i) + j) = CreateReverseDC(mFileName)) == NULL) {
						ErrorFileLoad();
						return;
					}
				}
				else {
					if ((*(*(mhBit + i) + j) = CreateBitmapDC(mFileName)) == NULL) {
						ErrorFileLoad();
						return;
					}
				}

				imageCount = (imageCount + 1) % 17;
			}
			imageCount = 0;
		}

		//-----------------------------------------
		// ���� �ý��� �ε�
		//-----------------------------------------
		SoundManager::GetInstance()->Init();
		SoundManager::GetInstance()->PlayBGM();

		mCurrentTime = GetTickCount();
		wsprintf(mSystemMsg, L"�ε��� �ɸ� �ð� : %d ms", mCurrentTime - mOldTime);
		SendMessage(hList, LB_INSERTSTRING, 0, (LPARAM)mSystemMsg);
		wsprintf(mSystemMsg, L"�ε� �Ϸ�!");
		SendMessage(hList, LB_INSERTSTRING, 0, (LPARAM)mSystemMsg);
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
		Unit **ppUnit;
		VECTOR2 *point;

		// ���� ������Ʈ
		SoundManager::GetInstance()->Update();

		// ������ �ൿ ����
		if (Unit::GetUnitCount() > 0) {
			ppUnit = Unit::GetUnitList();
			for (int i = 0; i < Unit::GetUnitCount(); i++) {
				(*ppUnit)->UnitProcess();
				*ppUnit++;
			}
		}

		// TODO : ��ɵ��� command queue�� �־ ����� �� �� ����.

		// ������ ����
		if (mMouseState == LBUTTONUP) {
			if (Unit::GetUnitCount() > 0) {
				// �巡�� ����
				mSelectedUnitCount = 0;
				int unitSize;
				ppUnit = Unit::GetUnitList();
				for (int i = 0; i < Unit::GetUnitCount(); i++) {
					if (mSelectedUnitCount >= 12) break;
					point = (*ppUnit)->GetPos();
					unitSize = (*ppUnit)->GetUnitSize();
					if ((point->x > mDragRect.left && point->x < mDragRect.right && point->y > mDragRect.top && point->y < mDragRect.bottom)
						|| Vec2Dist(&mMouseEP, point) < unitSize) {
						if (mSelectedUnitCount == 0) {
							for (int i = 0; i < 12; i++) {
								mSelectedUnit[i] = nullptr;
							}
						}
						mSelectedUnit[mSelectedUnitCount] = *ppUnit;
						mSelectedUnitCount++;
					}
					*ppUnit++;
				}
			}
			int count = 0;
			for (int i = 0; i < 12; i++) {
				if (mSelectedUnit[i] != nullptr) count++;
			}
			mSelectedUnitCount = count;
		}

		// ���� �̵����
		if (mMouseState == RBUTTONDOWN) {
			ppUnit = mSelectedUnit;
			for (int i = 0; i < 12; i++) {
				if (*ppUnit == nullptr) {
					break;
				}
				else {
					(*ppUnit)->GetMovePath()->clear();
					(*ppUnit)->GetMovePath()->push_front(mMousePoint);
					(*ppUnit)->Move();
				}
				*ppUnit++;
			}
			mMouseState = MOUSE_NONE;
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
		TextOut(mhBackBuffer, CLIENT_WIDTH / 2 - 100, CLIENT_HEIGHT / 2, L"�ε���", wcslen(L"�ε���"));

	}
	break;
	case GAME_TITLE:

		break;
	case GAME_ROOP:
	{
		HDC hRender;
		Unit** pUnit;
		VECTOR2 *point;
		Image *pImgInfo;
		int halfWidth;
		int halfHeight;

		hRender = CreateCompatibleDC(mhBackBuffer);

		// ��� �׸���
		SelectObject(hRender, mhBackgroundBit);
		BitBlt(mhBackBuffer, 0, 0, 800, 600, hRender, 0, 0, SRCCOPY);

		//------------------------------
		// ���õ� ���� �� �׸���
		//------------------------------
		if (mSelectedUnitCount != 0) {
			for (int i = 0; i < 12; i++) {
				if (mSelectedUnit[i] == nullptr) break;
				else {
					point = mSelectedUnit[i]->GetPos();
					pImgInfo = mSelectedUnit[i]->GetImgInfo();
					int unitSize = mSelectedUnit[i]->GetUnitSize() / 2;
					Ellipse(mhBackBuffer, point->x - unitSize - 5, point->y + unitSize, point->x + unitSize + 5, point->y + unitSize + 10);

				}
			}
		}


		//------------------------------
		// ���� �׸���
		//------------------------------
		pUnit = Unit::GetUnitList();
		for (int i = 0; i < Unit::GetUnitCount(); i++)
		{
			point = (*pUnit)->GetPos();
			pImgInfo = (*pUnit)->GetImgInfo();
			halfWidth = pImgInfo->bitWidth / 2;
			halfHeight = pImgInfo->bitHeight / 2;

			int renderIndex = (*pUnit)->GetRenderTarget();
			SelectObject(hRender, *(*(mhBit + (*pUnit)->GetUnitID()) + renderIndex));

			TransparentBlt(mhBackBuffer, point->x - halfWidth, point->y - halfHeight, pImgInfo->bitWidth, pImgInfo->bitHeight, hRender, 0, 0, pImgInfo->bitWidth, pImgInfo->bitHeight, pImgInfo->transColor);
			*pUnit++; // �����ͷ� Ž����

		}



		//SetBkColor(mhBackBuffer, RGB(0, 0, 0));
		SetBkMode(mhBackBuffer, TRANSPARENT);
		SetTextColor(mhBackBuffer, RGB(255, 255, 255));
		_stprintf(mFPS, _T("FPS:%-4d"), mnFPS);
		TextOut(mhBackBuffer, 0, 0, mFPS, _tcslen(mFPS));

		_stprintf(mUnitCount, _T("UnitCount:%-4d, mX: %-4.2f, mY: %-4.2f"), Unit::GetUnitCount(), mMousePoint.x, mMousePoint.y);
		TextOut(mhBackBuffer, 0, 20, mUnitCount, _tcslen(mUnitCount));

		_stprintf(mSystemMsg, _T("�������� ���� : %d"), mSelectedUnitCount);
		TextOut(mhBackBuffer, 0, 40, mSystemMsg, _tcslen(mSystemMsg));

		DEBUG_GAME
		(
			if (mSelectedUnitCount != 0) {
				if (mSelectedUnit[0] == nullptr) break;
				else {
					_stprintf(mSystemMsg, _T("TargetVector : %f, %f"), mSelectedUnit[0]->GetTarget()->x, mSelectedUnit[0]->GetTarget()->y);
					TextOut(mhBackBuffer, 0, 60, mSystemMsg, _tcslen(mSystemMsg));
					_stprintf(mSystemMsg, _T("State : %d"), mSelectedUnit[0]->GetState());
					TextOut(mhBackBuffer, 0, 80, mSystemMsg, _tcslen(mSystemMsg));
					_stprintf(mSystemMsg, _T("Anim : %d"), mSelectedUnit[0]->GetAnim());
					TextOut(mhBackBuffer, 0, 100, mSystemMsg, _tcslen(mSystemMsg));
				}
			}
		)
			DeleteDC(hRender);
		break;
	}
	case GAME_DESTROY:

		break;
	}

}


void Game::SceneRelease() {
	Unit::Release();
	DeleteObject(mhBackgroundBit);
	int count;

	for (int i = 0; i < MAX_UNIT_SPECIES; i++) {
		if (*(mhBit + i) != nullptr) {
			count = mpParents[i]->GetAllImageCount();
			for (int j = 0; j < count; j++) {
				if (*(*(mhBit + i) + j) != nullptr) {
					DeleteObject(*(*(mhBit + i) + j));
				}
			}
			delete[] * (mhBit + i);
		}
		delete mpParents[i];
	}
	delete[] mhBit;

	SoundManager::GetInstance()->Release();
}