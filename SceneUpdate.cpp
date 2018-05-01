#include "stdafx.h"

//-----------------------------------------------
// 게임에 필요한 정보를 업데이트 합니다.
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
		// 배경 이미지 로드
		//-----------------------------------
		wsprintf(mFileName, L"map\\map_01.bmp");
		if ((mhBackgroundBit = CreateBitmapDC(mFileName)) == NULL) {
			ErrorFileLoad();
			return;
		}

		//-----------------------------------------
		// 유닛 이미지 정보 로드
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
		// 사운드 시스템 로드
		//-----------------------------------------
		SoundManager::GetInstance()->Init();
		SoundManager::GetInstance()->PlayBGM();

		mCurrentTime = GetTickCount();
		wsprintf(mSystemMsg, L"로딩에 걸린 시간 : %d ms", mCurrentTime - mOldTime);
		SendMessage(hList, LB_INSERTSTRING, 0, (LPARAM)mSystemMsg);
		wsprintf(mSystemMsg, L"로딩 완료!");
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

		// 사운드 업데이트
		SoundManager::GetInstance()->Update();

		// 유닛의 행동 실행
		if (Unit::GetUnitCount() > 0) {
			ppUnit = Unit::GetUnitList();
			for (int i = 0; i < Unit::GetUnitCount(); i++) {
				(*ppUnit)->UnitProcess();
				*ppUnit++;
			}
		}

		// TODO : 명령들을 command queue에 넣어서 만들면 될 것 같다.

		// 유닛의 선택
		if (mMouseState == LBUTTONUP) {
			if (Unit::GetUnitCount() > 0) {
				// 드래그 선택
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

		// 유닛 이동명령
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
		}

		break;
	}
	case GAME_DESTROY:

		break;
	}
}
