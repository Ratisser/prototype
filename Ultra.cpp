#include "stdafx.h"
#include "Ultra.h"

int Ultra::msprStop[] = { 0 };
int Ultra::msprMove[] = { 0,1,2,3,4,5,6,7,8 };

Ultra::Ultra()
	:StarUnit()
{
	mUnitID = ULTRA;
	mAlliance = 2;
	mMoveSpeed = 8.0f;
	mUnitSize = 44;
	SetImg(128, 128, RGB(0,0,0));
	mStopSpr = msprStop;
	mMoveSpr = msprMove;
	mMoveSprCount = 9;
}


Ultra::~Ultra()
{
}

