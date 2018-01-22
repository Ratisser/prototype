#include "stdafx.h"
#include "Game.h"

//-----------------------------------------------
// 게임에 필요한 정보를 업데이트 합니다.
//-----------------------------------------------
void Game::SceneUpdate() {
	mCurrentTime = GetTickCount();

	switch (mGameState) {
	case GAME_INIT:
	{
		mOldTime = mCurrentTime;
		mSelectedCount = 0;
		int ImageCount = 0;

		// 이 카운트는 이미지를 반대로 그릴지 말지 결정 17마다 초기화
		// 왜 그런지는 모르겠으나 그림이 17방향을 유도하게 짜여져있음...(A*알고리즘에 의한 이동이 8방향에서 확장된 16방향으로 추정)

		//-----------------------------------
		// 배경 이미지 로드
		//-----------------------------------
		wsprintf(mSystemMsg, L"배경 로딩중...");
		SceneRender();
		wsprintf(mFileName, L"map\\map_01.bmp");
		if ((mhBackgroundBit = CreateBitmapDC(mFileName)) == NULL) {
			ErrorFileLoad();
			return;
		}

		//-----------------------------------------
		// 유닛 이미지 정보 로드
		//-----------------------------------------

		for (int i = 0; i < MAX_UNIT_SPECIES; i++) {
			LoadString(mhInst, mpParents[i]->GetFilePath(), mFilePath, 50);
			*(mhBit + i) = new HBITMAP[mpParents[i]->GetAllImageCount()];
			for (int j = 0; j < mpParents[i]->GetAllImageCount(); j++) {
				wsprintf(mSystemMsg, L"유닛 로딩중...(%d/%d)", j + 1, mpParents[i]->GetAllImageCount());
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
		wsprintf(mSystemMsg, L"로딩에 걸린 시간 : %d ms", mCurrentTime - mOldTime);
		Render();
		wsprintf(mSystemMsg, L"로딩 완료!");
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

		// 유닛의 행동 실행
		if (StarUnit::GetUnitCount() > 0) {
			pUnit = StarUnit::GetUnitList();
			for (int i = 0; i < StarUnit::GetUnitCount(); i++) {
				(*pUnit)->UnitProcess();
				*pUnit++;
			}
		}

		// 유닛의 선택
		if (mMouseState == LBUTTONUP) {
			if (StarUnit::GetUnitCount() > 0) {
				// 드래그 선택
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

		// 유닛 이동명령
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
