#include "stdafx.h"

int Ultra::msprStop[] = { 0 };
int Ultra::msprMove[] = { 0,1,2,3,4,5,6,7,8 };

Ultra::Ultra()
	:Unit()
{
	mUnitID = ULTRA;
	mAlliance = 2;
	mMoveSpeed = 8.0f;
	mUnitSize = 40;
	SetImg(128, 128, RGB(0,0,0));
	mpStopSpr = msprStop;
	mpMoveSpr = msprMove;
	mMoveSprCount = 9;
}


Ultra::~Ultra()
{
}

