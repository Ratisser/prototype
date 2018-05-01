#include "stdafx.h"

int Ghost::msprStop[] = { 3 };
int Ghost::msprMove[] = { 3,4,5,6,7,8,9,10,11 };

Ghost::Ghost()
	:Unit()
{
	mUnitID = GHOST;
	mAlliance = 1;
	mMoveSpeed = 4.0f;
	mUnitSize = 17;
	SetImg(64, 64, RGB(0, 0, 0));
	mpStopSpr = msprStop;
	mpMoveSpr = msprMove;
	mMoveSprCount = 8;
}


Ghost::~Ghost()
{
}


