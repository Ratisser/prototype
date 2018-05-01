#include "stdafx.h"

int Marine::msprStop[] = { 4 };
int Marine::msprMove[] = { 4,5,6,7,8,9,10,11,12 };
int Marine::msprAttack[] = { 0,1,2,3,2,3,2,3,2,3,2 };

Marine::Marine()
	:Unit()
{
	mUnitID = MARINE;
	mAlliance = 1;
	mMoveSpeed = 4.0f;
	mUnitSize = 15;
	mUnitSight = 200;
	mUnitAtkRange = 160;
	SetImg(64, 64, RGB(0, 0, 0));
	mpStopSpr = msprStop;
	mpMoveSpr = msprMove;
	mpAtkSpr = msprAttack;
	mMoveSprCount = 9;
	mAtkSprCount = 11;
	mAtkFrame = 2;
}


Marine::~Marine()
{
}