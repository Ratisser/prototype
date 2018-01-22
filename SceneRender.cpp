#include "stdafx.h"
#include "Game.h"

//-----------------------------------------------
// 실제 화면에 보이는 장면을 처리합니다
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
		HDC hRender;
		StarUnit** pUnit;
		VECTOR2 *point;
		Image *ImgInfo;
		int halfWidth;
		int halfHeight;

		hRender = CreateCompatibleDC(mhBackBuffer);

		// 배경 그리기
		SelectObject(hRender, mhBackgroundBit);
		BitBlt(mhBackBuffer, 0, 0, 800, 600, hRender, 0, 0, SRCCOPY);

		//------------------------------
		// 선택된 유닛 원 그리기
		//------------------------------
		if (mSelectedCount != 0) {
			for (int i = 0; i < 12; i++)
				if (mSelectedUnit[i] == nullptr) break;
				else {
					point = mSelectedUnit[i]->GetPos();
					ImgInfo = mSelectedUnit[i]->GetImgInfo();
					int unitSize = mSelectedUnit[i]->GetUnitSize() / 2;
					Ellipse(mhBackBuffer, point->x - unitSize - 5, point->y + unitSize, point->x + unitSize + 5, point->y + unitSize + 10);

				}

		}


		//------------------------------
		// 유닛 그리기
		//------------------------------
		pUnit = StarUnit::GetUnitList();
		for (int i = 0; i < StarUnit::GetUnitCount(); i++) {
			point = (*pUnit)->GetPos();
			ImgInfo = (*pUnit)->GetImgInfo();
			halfWidth = ImgInfo->bitWidth / 2;
			halfHeight = ImgInfo->bitHeight / 2;

			int renderIndex = (*pUnit)->GetRenderTarget();
			SelectObject(hRender, *(*(mhBit + (*pUnit)->GetUnitID())+renderIndex));
			TransparentBlt(mhBackBuffer, point->x - halfWidth, point->y - halfHeight, ImgInfo->bitWidth, ImgInfo->bitHeight, hRender, 0, 0, ImgInfo->bitWidth, ImgInfo->bitHeight, ImgInfo->transColor);
			*pUnit++; // 포인터로 탐색함
		}

		SetBkColor(mhBackBuffer, RGB(0, 0, 0));
		SetTextColor(mhBackBuffer, RGB(255, 255, 255));
		_stprintf(mFPS, _T("FPS:%-4d"), mnFPS);
		TextOut(mhBackBuffer, 0, 0, mFPS, _tcslen(mFPS));

		_stprintf(mUnitCount, _T("UnitCount:%-4d, mX: %-4.2f, mY: %-4.2f"), StarUnit::GetUnitCount(), mMousePoint.x, mMousePoint.y);
		TextOut(mhBackBuffer, 0, 20, mUnitCount, _tcslen(mUnitCount));

		_stprintf(mSystemMsg, _T("선택중인 유닛 : %d"), mSelectedCount);
		TextOut(mhBackBuffer, 0, 40, mSystemMsg, _tcslen(mSystemMsg));

		DeleteDC(hRender);

		break;
	}
	case GAME_DESTROY:

		break;
	}

}
