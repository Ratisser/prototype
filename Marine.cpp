#include "stdafx.h"
#include "Marine.h"

int Marine::msprStop[] = { 0 };
int Marine::msprMove[] = { 4,5,6,7,8,9,10,11,12};

Marine::Marine()
	:StarUnit()
{
	mUnitID = MARINE;
	mMoveSpeed = 5.0f;
	mUnitSize = 17;
	SetImg(64, 64, RGB(0, 0, 0));
}


Marine::~Marine()
{
}


void Marine::onStop() {
	mAnim = 0;
	mRenderTarget = ((mDegree < 9) ? mDegree * 2 : 35 - mDegree * 2) + 17 * msprStop[mAnim] - (mDegree == 9);
}

void Marine::onMove() {
	mvPos.x += mvDirection.x * mMoveSpeed;
	mvPos.y += mvDirection.y * mMoveSpeed;
	mRenderTarget = ((mDegree < 9) ? mDegree * 2 : 35 - mDegree * 2) + 17 * msprMove[mAnim] - (mDegree == 9);
	mAnim++;
	mAnim = mAnim % 8;

}