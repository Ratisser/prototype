#include "stdafx.h"
#include "Zergling.h"


const int Zergling::TOTAL_IMAGE_COUNT = 296;
const int Zergling::UNIT_IMAGE_COUNT = 289;
int Zergling::msprStop[] = { 0 };
int Zergling::msprMove[] = { 4,5,6,7,8,9,10,11};

Zergling::Zergling()
	:Unit()
{
	mUnitID = ZERGLING;
	mBitmapSize = 128;
	mMoveSpeed = 15.0f;
}


Zergling::~Zergling()
{
}

void Zergling::onStop() {
	mAnim = 0;
	mRenderTarget = ((mDegree < 9) ? mDegree * 2 : 35 - mDegree * 2) + (17 * msprStop[mAnim]) - (mDegree == 9);
}

void Zergling::onMove() {
	mPos.x += mDirection.x * mMoveSpeed;
	mPos.y += mDirection.y * mMoveSpeed;
	mRenderTarget = ((mDegree < 9) ? mDegree * 2 : 35 - mDegree * 2) + (17 * msprMove[mAnim]) - (mDegree == 9);
	mAnim++;
	mAnim = mAnim % 8;

}