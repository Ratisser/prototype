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
