#include "stdafx.h"
#include "Sara.h"

int Sara::msprStop[] = { 0 };
int Sara::msprMove[] = { 1,1,1,1,1,2,2,2,2,2 };

Sara::Sara()
	:StarUnit()
{
	mUnitID = SARA;
	mMoveSpeed = 5.0f;
	mUnitSize = 31;
	SetImg(43, 62, RGB(255, 255, 255));
}


Sara::~Sara()
{
}

void Sara::onStop() {
	mAnim = 0;
	mRenderTarget = ((mDegree < 9) ? mDegree * 2 : 35 - mDegree * 2) + 17 * msprStop[mAnim] - (mDegree == 9);
}

void Sara::onMove() {
	mvPos.x += mvDirection.x * mMoveSpeed;
	mvPos.y += mvDirection.y * mMoveSpeed;
	mRenderTarget = ((mDegree < 9) ? mDegree * 2 : 35 - mDegree * 2) + 17 * msprMove[mAnim] - (mDegree == 9);
	mAnim++;
	mAnim = mAnim % 10;

}