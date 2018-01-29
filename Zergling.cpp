#include "stdafx.h"
#include "Zergling.h"

int Zergling::msprStop[] = { 0 };
int Zergling::msprMove[] = { 4,5,6,7,8,9,10,11};

Zergling::Zergling()
	:StarUnit()
{
	mUnitID = ZERGLING;
	mAlliance = 2;
	mMoveSpeed = 8.0f;
	mUnitSize = 14;
	SetImg(128, 128, RGB(0, 0, 0));
	mStopSpr = msprStop;
	mMoveSpr = msprMove;
	mMoveSprCount = 8;
}


Zergling::~Zergling()
{
}

