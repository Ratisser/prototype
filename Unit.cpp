#include "stdafx.h"

Unit* Unit::mpUnitList[MAX_UNIT_COUNT];
int Unit::mUnitCount = 0;

Unit::Unit() {
	SetPos(Game::GetInstance()->GetMousePoint());
	Stop();
}

Unit::~Unit() {
}

void Unit::SetImg(int width, int height, UINT rgbColor) {
	mUnitImage.bitWidth = width;
	mUnitImage.bitHeight = height;
	mUnitImage.transColor = rgbColor;
}

void Unit::UnitProcess() {

	DWORD curTime = Game::GetInstance()->GetTime();
	if (0 == mMovePath.empty()) mvTarget = mMovePath.front();
	Vec2Dir(&mvDirection, &mvPos, &mvTarget);
	mDegree = TODEG(Vec2Theta(&mvDirection)) / 20;


	switch (mUnitState)
	{
	case STOP:
		mCollisionCount = 0;
		onStop();
		if (curTime - mdwWaitTime > 100) {
			SetState(WATCH);
		}
		break;
	case WATCH:
		checkRange();

		break;
	case MOVE:
	{
		if ((curTime - mdwAnimTime) > 33) {
			onMove();
			mdwAnimTime = curTime;
		}
		// 충돌 검사
		Unit** ppUnit = Unit::GetUnitList();
		VECTOR2 *curUnitPoint;
		int unitSize = mUnitSize;
		int curUnitSize;
		int distance;
		int nUnitCount = Unit::GetUnitCount();
		for (int i = 0; i < nUnitCount; i++) {
			if ((*ppUnit) == this) {
				*ppUnit++;
				continue;
			}
			curUnitPoint = (*ppUnit)->GetPos();
			curUnitSize = (*ppUnit)->GetUnitSize();
			distance = curUnitSize + unitSize;
			if (Vec2Dist(&mvPos, curUnitPoint) < distance) {
				if (0 && (*ppUnit)->GetState() == MOVE || (*ppUnit)->GetState() == COLLISION) {
					mMoveSpeed *= -1;
					onMove();
					mMoveSpeed *= -1;
					SetState(COLLISION);
					return;
				}
				else {
					// TODO : 길찾기 알고리즘 (현재는 겹칠경우 방향을 틀어서 이동)
					mMoveSpeed *= -1;
					onMove();
					mMoveSpeed *= -1;
					VECTOR2 temp = Vec2Rotate(&mvDirection, 45);
					temp.x = temp.x * (20+curUnitSize) + mvPos.x;
					temp.y = temp.y * (20+curUnitSize) + mvPos.y;
					mMovePath.push_front(temp);
					SetState(COLLISION);
					return;
				}
			}
			*ppUnit++;

		}

		if (Vec2Dist(&mvPos, &mvTarget) < 10) {
			mMovePath.pop_front();
			if (mMovePath.empty()) {
				Stop();
			}
		}

	}
	break;
	case ATTACK:
		Vec2Dir(&mvDirection, &mvPos, &mvTarget);
		mvTarget = *(mpUnitAtkTarget->GetPos());
		if (Vec2Dist(&mvPos, &mvTarget) < mUnitAtkRange) {
			if (curTime - mdwWaitTime < 1000) {
				if ((curTime - mdwAnimTime) > 33) {
					onAttack();
					mdwAnimTime = curTime;
				}
			}
			else {
				Attack();
			}
		}
		else {
			Vec2Dir(&mvDirection, &mvPos, &mvTarget);
			int needToMove = mUnitSight - mUnitAtkRange + 20;
			VECTOR2 temp;
			temp.x = mvDirection.x * needToMove + mvPos.x;
			temp.y = mvDirection.y * needToMove + mvPos.y;
			mMovePath.push_front(temp);
			Move();
		}
		break;
	case COLLISION:
	{

		DWORD curTime = Game::GetInstance()->GetTime();
		if (curTime - mdwWaitTime > 100) {
			if (++mCollisionCount > 6) {
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
	mpUnitAtkTarget = nullptr;
	for (int i = 0; i < nUnitCount; i++) {
		if ((Vec2Dist(&mvPos, (*ppUnit)->GetPos()) < mUnitSight) && (*ppUnit)->GetAlliance() != mAlliance) {
			if (mpUnitAtkTarget == nullptr || (Vec2Dist(&mvPos, (*ppUnit)->GetPos())) < (Vec2Dist(&mvPos, mpUnitAtkTarget->GetPos()))) {
				mpUnitAtkTarget = *ppUnit;
				*ppUnit++;
				continue;
			}
		}
		*ppUnit++;
	}
	if (mpUnitAtkTarget != nullptr) {
		mvTarget = *(mpUnitAtkTarget->GetPos());
		Attack();
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
	mRenderTarget = ((mDegree < 9) ? mDegree * 2 : 35 - mDegree * 2) + 17 * mpStopSpr[mAnim] - (mDegree == 9);
}

void Unit::onMove() {
	mvPos.x += mvDirection.x * mMoveSpeed;
	mvPos.y += mvDirection.y * mMoveSpeed;
	mRenderTarget = ((mDegree < 9) ? mDegree * 2 : 35 - mDegree * 2) + 17 * mpMoveSpr[mAnim] - (mDegree == 9);
	mAnim++;
	mAnim = mAnim % mMoveSprCount;

}

void Unit::onAttack() {
	mRenderTarget = ((mDegree < 9) ? mDegree * 2 : 35 - mDegree * 2) + 17 * mpAtkSpr[mAnim] - (mDegree == 9);
	if (mAnim == 3) SoundManager::GetInstance()->PlayAtk();
	if (10 > mAnim) mAnim++;

}

void Unit::Stop() {
		mdwWaitTime = Game::GetInstance()->GetTime();
		SetState(STOP);
		onChangeState();
}

void Unit::Move() {
		SetState(MOVE);
		onChangeState();
		mCollisionCount = 0;
}

void Unit::Attack() {
	if (mUnitState == ATTACK) {
		mAnim = mAtkFrame;
	}
	else {
		mAnim = 0;

	}
	mdwWaitTime = Game::GetInstance()->GetTime();
	SetState(ATTACK);
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
	Game::GetInstance()->ClearSelectedUnit();
	SendMessage(Game::GetInstance()->hList, LB_INSERTSTRING, 0, (LPARAM)L"유닛을 삭제했습니다.");
	return true;

}