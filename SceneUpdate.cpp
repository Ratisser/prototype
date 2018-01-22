#include "stdafx.h"
#include "Game.h"

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
		int ImageCount = 0;

		// �� ī��Ʈ�� �̹����� �ݴ�� �׸��� ���� ���� 17���� �ʱ�ȭ
		// �� �׷����� �𸣰����� �׸��� 17������ �����ϰ� ¥��������...(A*�˰��� ���� �̵��� 8���⿡�� Ȯ��� 16�������� ����)

		//-----------------------------------
		// ��� �̹��� �ε�
		//-----------------------------------
		wsprintf(mSystemMsg, L"��� �ε���...");
		SceneRender();
		wsprintf(mFileName, L"map\\map_01.bmp");
		if ((mhBackgroundBit = CreateBitmapDC(mFileName)) == NULL) {
			ErrorFileLoad();
			return;
		}

		//-----------------------------------------
		// ���� �̹��� ���� �ε�
		//-----------------------------------------

		for (int i = 0; i < MAX_UNIT_SPECIES; i++) {
			LoadString(mhInst, mpParents[i]->GetFilePath(), mFilePath, 50);
			*(mhBit + i) = new HBITMAP[mpParents[i]->GetAllImageCount()];
			for (int j = 0; j < mpParents[i]->GetAllImageCount(); j++) {
				wsprintf(mSystemMsg, L"���� �ε���...(%d/%d)", j + 1, mpParents[i]->GetAllImageCount());
				wsprintf(mFileName, L"%simg%d.bmp", mFilePath, j + 1);
				Render();
				if (ImageCount % 2 == 1 && j < mpParents[i]->GetUnitImageCount()) {
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

				ImageCount = (ImageCount + 1) % 17;
			}
			ImageCount = 0;
		}

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
		StarUnit** pUnit;
		VECTOR2 *point;

		// ������ �ൿ ����
		if (StarUnit::GetUnitCount() > 0) {
			pUnit = StarUnit::GetUnitList();
			for (int i = 0; i < StarUnit::GetUnitCount(); i++) {
				(*pUnit)->UnitProcess();
				*pUnit++;
			}
		}

		// ������ ����
		if (mMouseState == LBUTTONUP) {
			if (StarUnit::GetUnitCount() > 0) {
				// �巡�� ����
				mSelectedCount = 0;
				int unitSize;
				pUnit = StarUnit::GetUnitList();
				for (int i = 0; i < StarUnit::GetUnitCount(); i++) {
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
