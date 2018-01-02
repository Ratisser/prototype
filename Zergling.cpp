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
	mMoveSpeed = 10.0f;
	mUnitSize = 14;
	SetImg(128, 128, RGB(0, 0, 0));
}


Zergling::~Zergling()
{
}

void Zergling::onStop() {
	mAnim = 0;
	mRenderTarget = ((mDegree < 9) ? mDegree * 2 : 35 - mDegree * 2) + (17 * msprStop[mAnim]) - (mDegree == 9);
}

void Zergling::onMove() {
	mvPos.x += mvDirection.x * mMoveSpeed;
	mvPos.y += mvDirection.y * mMoveSpeed;
	mRenderTarget = ((mDegree < 9) ? mDegree * 2 : 35 - mDegree * 2) + (17 * msprMove[mAnim]) - (mDegree == 9);
	mAnim++;
	mAnim = mAnim % 8;

}