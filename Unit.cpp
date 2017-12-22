#include "stdafx.h"
#include "Unit.h"

Unit* Unit::mpUnitList[MAX_UNIT_COUNT];
int Unit::mUnitCount = 0;

Unit::Unit() {
	SetPos(Game::GetInstance()->GetMousePoint());
	Stop();
}

Unit::~Unit() {

}

void Unit::UnitProcess() {
	checkRange();

	Vec2Dir(&mDirection, &mPos, &mvTarget);
	mDegree = TODEG(Vec2Theta(&mDirection)) / 20;

	switch (mUnitState)
	{
	case STOP:
		onStop();
		break;
	case WATCH:

		break;
	case MOVE:
	{
		DWORD curTime = Game::GetInstance()->GetTime();
		if ((curTime - mdwAnimTime) > 50) {
			onMove();
			mdwAnimTime = curTime;
		}

		if ((mPos.x - mvTarget.x) * (mPos.x - mvTarget.x) < 100 && (mPos.y - mvTarget.y)*(mPos.y - mvTarget.y) < 100) {
			mUnitState = STOP;
		}
	}
	break;
	case ATTACK:

		break;
	case COLLISION:

		break;
	}
}

void Unit::checkRange() {

}

bool Unit::AddUnit(int i) {
	if (mUnitCount >= MAX_UNIT_COUNT) {
		return false;
	}
	mUnitCount++;
	switch (i)
	{
	case MARINE:
		mpUnitList[mUnitCount - 1] = new Marine;
		SendMessage(Game::GetInstance()->hList, LB_INSERTSTRING, 0, (LPARAM)L"마린을 생성했습니다.");
		break;
	case ZERGLING:
		mpUnitList[mUnitCount - 1] = new Zergling;
		SendMessage(Game::GetInstance()->hList, LB_INSERTSTRING, 0, (LPARAM)L"저글링을 생성했습니다.");
		break;
	case ULTRA:
		mpUnitList[mUnitCount - 1] = new Ultra;
		SendMessage(Game::GetInstance()->hList, LB_INSERTSTRING, 0, (LPARAM)L"울트라리스크를 생성했습니다.");
		break;
	}
	return true;
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



void Unit::SetState(UnitState state) {
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
	mRenderTarget = 0;

	mdwAnimTime = Game::GetInstance()->GetTime();
	mAnim = 0;

}