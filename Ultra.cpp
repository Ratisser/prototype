#include "stdafx.h"
#include "Ultra.h"

int Ultra::msprStop[] = { 0 };
int Ultra::msprMove[] = { 0,1,2,3,4,5,6,7,8 };

Ultra::Ultra()
	:StarUnit()
{
	mUnitID = ULTRA;
	mMoveSpeed = 8.0f;
	mUnitSize = 44;
	SetImg(128, 128, RGB(0,0,0));
}


Ultra::~Ultra()
{
}

void Ultra::onStop() {
	mAnim = 0;
	mRenderTarget = ((mDegree < 9) ? mDegree * 2 : 35 - mDegree * 2) + 17 * msprStop[mAnim] - (mDegree == 9);
}

void Ultra::onMove() {
	mvPos.x += mvDirection.x * mMoveSpeed;
	mvPos.y += mvDirection.y * mMoveSpeed;
	mRenderTarget = ((mDegree < 9) ? mDegree * 2 : 35 - mDegree * 2) + 17 * msprMove[mAnim] - (mDegree == 9);
	mAnim++;
	mAnim = mAnim % 9;

}
