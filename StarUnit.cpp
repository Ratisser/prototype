#include "stdafx.h"
#include "Unit.h"

StarUnit* StarUnit::mpUnitList[MAX_UNIT_COUNT];
int StarUnit::mUnitCount = 0;

StarUnit::StarUnit() {
	SetPos(Game::GetInstance()->GetMousePoint());
	Stop();
}

StarUnit::~StarUnit() {

}

void StarUnit::SetImg(int width, int height, UINT rgbColor) {
	mUnitImage.bitWidth = width;
	mUnitImage.bitHeight = height;
	mUnitImage.transColor = rgbColor;
}

void StarUnit::UnitProcess() {
	

	Vec2Dir(&mvDirection, &mvPos, &mvTarget);
	mDegree = TODEG(Vec2Theta(&mvDirection)) / 20;

	switch (mUnitState)
	{
	case STOP:
		mCollisionCount = 0;
		onStop();
		SetState(WATCH);
		break;
	case WATCH:
		checkRange();

		break;
	case MOVE:
	{
		// TODO : �ִϸ��̼ǰ� ���¾�����Ʈ�� �и��� ��(������ ���ؼ�)
		DWORD curTime = Game::GetInstance()->GetTime();
		if ((curTime - mdwAnimTime) > 33) {
			onMove();
			mdwAnimTime = curTime;
		}
		// �浹 �˻�
		StarUnit** pUnit = StarUnit::GetUnitList();
		VECTOR2 *point;
		int unitSize = mUnitSize * mUnitSize;
		int curUnitSize;
		int distance;
		int nUnitCount = StarUnit::GetUnitCount();
		for (int i = 0; i < nUnitCount; i++) {
			if ((*pUnit) == this) {
				*pUnit++;
				continue;
			}
			point = (*pUnit)->GetPos();
			curUnitSize = (*pUnit)->GetUnitSize();
			curUnitSize = curUnitSize * curUnitSize;
			distance = curUnitSize + unitSize;
			if (Vec2Dist(&mvPos, point)< distance) {
				if ((*pUnit)->GetState() == MOVE || (*pUnit)->GetState() == COLLISION) {
					mMoveSpeed *= -1;
					onMove();
					mMoveSpeed *= -1;
					SetState(COLLISION);
					return;
				}
				else {
					// TODO : ��ã�� �˰���
					mMoveSpeed *= -1;
					onMove();
					mMoveSpeed *= -1;
					Stop();
					return;
				}
			}
			*pUnit++;

		}

		if (Vec2Dist(&mvPos,&mvTarget) < 100) {
			mUnitState = STOP;
		}
	}
	break;
	case ATTACK:

		break;
	case COLLISION:
	{

		DWORD curTime = Game::GetInstance()->GetTime();
		if (curTime - mdwWaitTime > 500) {
			if (++mCollisionCount > 5) {
				Stop();
				break;
			}
			SetState(MOVE);
			mdwWaitTime = curTime;
		}

	}
	break;
	}
}

void StarUnit::checkRange() {
	int nUnitCount = StarUnit::GetUnitCount();
}

bool StarUnit::AddUnit(int i) {
	if (mUnitCount >= MAX_UNIT_COUNT) {
		return false;
	}
	mUnitCount++;
	mpUnitList[mUnitCount - 1] = Game::mpParents[i]->GetInstance();
	//switch (i)
	//{
	//case MARINE:
	//	mpUnitList[mUnitCount - 1] = Game::mpParents[i]->GetInstance();
	//	SendMessage(Game::GetInstance()->hList, LB_INSERTSTRING, 0, (LPARAM)L"������ �����߽��ϴ�.");
	//	break;
	//case ZERGLING:
	//	mpUnitList[mUnitCount - 1] = Game::mpParents[i]->GetInstance();
	//	SendMessage(Game::GetInstance()->hList, LB_INSERTSTRING, 0, (LPARAM)L"���۸��� �����߽��ϴ�.");
	//	break;
	//case ULTRA:
	//	mpUnitList[mUnitCount - 1] = Game::mpParents[i]->GetInstance();
	//	SendMessage(Game::GetInstance()->hList, LB_INSERTSTRING, 0, (LPARAM)L"��Ʈ�󸮽�ũ�� �����߽��ϴ�.");
	//	break;
	//case SARA:
	//	mpUnitList[mUnitCount - 1] = Game::mpParents[i]->GetInstance();
	//	SendMessage(Game::GetInstance()->hList, LB_INSERTSTRING, 0, (LPARAM)L"Sara�� �����߽��ϴ�.");
	//	break;
	//}
	return true;
}

void StarUnit::onStop() {
	mAnim = 0;
	mRenderTarget = ((mDegree < 9) ? mDegree * 2 : 35 - mDegree * 2) + 17 * mStopSpr[mAnim] - (mDegree == 9);
}

void StarUnit::onMove() {
	mvPos.x += mvDirection.x * mMoveSpeed;
	mvPos.y += mvDirection.y * mMoveSpeed;
	mRenderTarget = ((mDegree < 9) ? mDegree * 2 : 35 - mDegree * 2) + 17 * mMoveSpr[mAnim] - (mDegree == 9);
	mAnim++;
	mAnim = mAnim % mMoveSprCount;

}

void StarUnit::Stop() {
	if (mUnitState != STOP) {
		SetState(STOP);
		onChangeState();
	}
}

void StarUnit::Move() {
	if (mUnitState != MOVE) {
		SetState(MOVE);
		onChangeState();
	}
}



void StarUnit::SetState(eUnitState state) {
	mUnitState = state;
}

void StarUnit::Release() {
	if (mUnitCount > 0)
	{
		for (int i = 0; i < mUnitCount; i++) {
			delete mpUnitList[i];
		}
	}
}

void StarUnit::onChangeState() {
	mdwAnimTime = Game::GetInstance()->GetTime();
	mAnim = 0;

}

bool StarUnit::RemoveUnit() {
	if (mUnitCount == 0) {
		SendMessage(Game::GetInstance()->hList, LB_INSERTSTRING, 0, (LPARAM)L"������ ������ �����ϴ�.");
		return false;
	}
	for (int i = 0; i < mUnitCount; i++) {
		delete mpUnitList[i];
	}
	mUnitCount = 0;
	SendMessage(Game::GetInstance()->hList, LB_INSERTSTRING, 0, (LPARAM)L"������ �����߽��ϴ�.");
	return true;

}