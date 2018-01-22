#include "stdafx.h"
#include "Ghost.h"

int Ghost::msprStop[] = { 3 };
int Ghost::msprMove[] = { 3,4,5,6,7,8,9,10,11 };

Ghost::Ghost()
	:StarUnit()
{
	mUnitID = GHOST;
	mMoveSpeed = 5.0f;
	mUnitSize = 17;
	SetImg(64, 64, RGB(0, 0, 0));
}


Ghost::~Ghost()
{
}


void Ghost::onStop() {
	mAnim = 0;
	mRenderTarget = ((mDegree < 9) ? mDegree * 2 : 35 - mDegree * 2) + 17 * msprStop[mAnim] - (mDegree == 9);
}

void Ghost::onMove() {
	mvPos.x += mvDirection.x * mMoveSpeed;
	mvPos.y += mvDirection.y * mMoveSpeed;
	mRenderTarget = ((mDegree < 9) ? mDegree * 2 : 35 - mDegree * 2) + 17 * msprMove[mAnim] - (mDegree == 9);
	mAnim++;
	mAnim = mAnim % 8;

}