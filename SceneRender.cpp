#include "stdafx.h"

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
		for (int i = 0; i < Unit::GetUnitCount(); i++) {
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

		DEBUG_GAME(
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
