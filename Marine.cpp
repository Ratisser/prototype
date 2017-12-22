#include "Marine.h"
#include "stdafx.h"


const int Marine::TOTAL_IMAGE_COUNT = 229;
const int Marine::UNIT_IMAGE_COUNT = 221;
int Marine::msprStop[] = { 0 };
int Marine::msprMove[] = { 4,5,6,7,8,9,10,11,12};

Marine::Marine()
	:Unit()
{
	mUnitID = MARINE;
	mBitmapSize = 64;
	mMoveSpeed = 5.0f;
}


Marine::~Marine()
{
}


void Marine::onStop() {
	mAnim = 0;
	mRenderTarget = ((mDegree < 9) ? mDegree * 2 : 35 - mDegree * 2) + 17 * msprStop[mAnim] - (mDegree == 9);
}

void Marine::onMove() {
	mPos.x += mDirection.x * mMoveSpeed;
	mPos.y += mDirection.y * mMoveSpeed;
	mRenderTarget = ((mDegree < 9) ? mDegree * 2 : 35 - mDegree * 2) + 17 * msprMove[mAnim] - (mDegree == 9);
	mAnim++;
	mAnim = mAnim % 8;

}