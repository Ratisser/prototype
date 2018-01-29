#include "stdafx.h"

Unit* Unit::mpUnitList[MAX_UNIT_COUNT];
int Unit::mUnitCount = 0;

Unit::Unit() {
	mNearUnitList = new List;
	SetPos(Game::GetInstance()->GetMousePoint());
	Stop();
}

Unit::~Unit() {
	delete mNearUnitList;
}

void Unit::SetImg(int width, int height, UINT rgbColor) {
	mUnitImage.bitWidth = width;
	mUnitImage.bitHeight = height;
	mUnitImage.transColor = rgbColor;
}

void Unit::UnitProcess() {
	

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
		// TODO : 애니메이션과 상태업데이트를 분리할 것(나중을 위해서)
		DWORD curTime = Game::GetInstance()->GetTime();
		if ((curTime - mdwAnimTime) > 33) {
			onMove();
			mdwAnimTime = curTime;
		}
		// 충돌 검사
		Unit** pUnit = Unit::GetUnitList();
		VECTOR2 *point;
		int unitSize = mUnitSize * mUnitSize;
		int curUnitSize;
		int distance;
		int nUnitCount = Unit::GetUnitCount();
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
					// TODO : 길찾기 알고리즘 (현재는 겹칠경우 반대로 이동)
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

void Unit::checkRange() {
	int nUnitCount = Unit::GetUnitCount();
	Unit **ppUnit = GetUnitList();
	mUnitAtkTarget = nullptr;
	for (int i = 0; i < nUnitCount; i++) {
		if ((Vec2Dist(&mvPos, (*ppUnit)->GetPos()) < mUnitSight * mUnitSight) && (*ppUnit)->GetAlliance() != mAlliance) {
			if (mUnitAtkTarget == nullptr || (Vec2Dist(&mvPos, (*ppUnit)->GetPos())) < (Vec2Dist(&mvPos, mUnitAtkTarget->GetPos()))) {
				mUnitAtkTarget = *ppUnit;
				*ppUnit++;
				continue;
			}
		}
		*ppUnit++;
	}
	if (mUnitAtkTarget != nullptr) {
		SetState(ATTACK);
	}
}

bool Unit::AddUnit(int i) {
	if (mUnitCount >= MAX_UNIT_COUNT) {
		return false;
	}
	mUnitCount++;
	mpUnitList[mUnitCount - 1] = Game::mpParents[i]->GetInstance();
	//switch (i)
	//{
	//case MARINE:
	//	mpUnitList[mUnitCount - 1] = Game::mpParents[i]->GetInstance();
	//	SendMessage(Game::GetInstance()->hList, LB_INSERTSTRING, 0, (LPARAM)L"마린을 생성했습니다.");
	//	break;
	//case ZERGLING:
	//	mpUnitList[mUnitCount - 1] = Game::mpParents[i]->GetInstance();
	//	SendMessage(Game::GetInstance()->hList, LB_INSERTSTRING, 0, (LPARAM)L"저글링을 생성했습니다.");
	//	break;
	//case ULTRA:
	//	mpUnitList[mUnitCount - 1] = Game::mpParents[i]->GetInstance();
	//	SendMessage(Game::GetInstance()->hList, LB_INSERTSTRING, 0, (LPARAM)L"울트라리스크를 생성했습니다.");
	//	break;
	//case SARA:
	//	mpUnitList[mUnitCount - 1] = Game::mpParents[i]->GetInstance();
	//	SendMessage(Game::GetInstance()->hList, LB_INSERTSTRING, 0, (LPARAM)L"Sara를 생성했습니다.");
	//	break;
	//}
	return true;
}

void Unit::onStop() {
	mAnim = 0;
	mRenderTarget = ((mDegree < 9) ? mDegree * 2 : 35 - mDegree * 2) + 17 * mStopSpr[mAnim] - (mDegree == 9);
}

void Unit::onMove() {
	mvPos.x += mvDirection.x * mMoveSpeed;
	mvPos.y += mvDirection.y * mMoveSpeed;
	mRenderTarget = ((mDegree < 9) ? mDegree * 2 : 35 - mDegree * 2) + 17 * mMoveSpr[mAnim] - (mDegree == 9);
	mAnim++;
	mAnim = mAnim % mMoveSprCount;

}

void Unit::Stop() {
	if (mUnitState != STOP) {
		SetState(STOP);
		onChangeState();
	}
}

void Unit::Move() {
	if (mUnitState != MOVE) {
		SetState(MOVE);
		onChangeState();
	}
}



void Unit::SetState(eUnitState state) {
	mUnitState = state;
}

void Unit::Release() {
	if (mUnitCount > 0)
	{
		for (int i = 0; i < mUnitCount; i++) {
			delete mpUnitList[i];
		}
	}
}

void Unit::onChangeState() {
	mdwAnimTime = Game::GetInstance()->GetTime();
	mAnim = 0;

}

bool Unit::RemoveUnit() {
	if (mUnitCount == 0) {
		SendMessage(Game::GetInstance()->hList, LB_INSERTSTRING, 0, (LPARAM)L"삭제할 유닛이 없습니다.");
		return false;
	}
	for (int i = 0; i < mUnitCount; i++) {
		delete mpUnitList[i];
	}
	mUnitCount = 0;
	SendMessage(Game::GetInstance()->hList, LB_INSERTSTRING, 0, (LPARAM)L"유닛을 삭제했습니다.");
	return true;

}