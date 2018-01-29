#include "stdafx.h"

int Marine::msprStop[] = { 0 };
int Marine::msprMove[] = { 4,5,6,7,8,9,10,11,12};

Marine::Marine()
	:Unit()
{
	mUnitID = MARINE;
	mAlliance = 1;
	mMoveSpeed = 4.0f;
	mUnitSize = 17;
	mUnitSight = 200;
	SetImg(64, 64, RGB(0, 0, 0));
	mStopSpr = msprStop;
	mMoveSpr = msprMove;
	mMoveSprCount = 8;
}


Marine::~Marine()
{
}

