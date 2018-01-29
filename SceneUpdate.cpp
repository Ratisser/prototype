#include "stdafx.h"

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
		// �� ī��Ʈ�� �̹����� �ݴ�� �׸��� ���� ���� 17���� �ʱ�ȭ
		// �� �׷����� �𸣰����� �׸��� 17������ �����ϰ� ¥��������...
		// A*�˰��� ���� �̵��� 8���⿡�� Ȯ��� 16�������� ����
		// �׷��ٸ� A* path find�� 16ĭ�� �Ѵ� ���ΰ�...?

		//-----------------------------------
		// ��� �̹��� �ε�
		//-----------------------------------
		//wsprintf(mSystemMsg, L"��� �ε���...");
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
				//wsprintf(mSystemMsg, L"���� �ε���...(%d/%d)", j + 1, mpParents[i]->GetAllImageCount());
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
						|| Vec2Dist(&mMouseEP, point) < unitSize*unitSize) {
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
					(*ppUnit)->SetTargetVector(&mMousePoint);
					(*ppUnit)->Move();
				}
				*ppUnit++;
			}
		}

		break;
	}
	case GAME_DESTROY:

		break;
	}
}
