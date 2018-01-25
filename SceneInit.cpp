#include <stdio.h>

#include "stdafx.h"
#include "Game.h"


//-----------------------------------------------
// 장면이 시작되기 전 초기화 작업을 합니다.
// 추가 초기화 작업은 SceneUpdate에서 합니다.
//-----------------------------------------------
void Game::SceneInit()
{
	// 이미지 DC들의 메모리 할당
	//mhMarineBit =	new	HBITMAP[mParents[0]->GetAllImageCount()];
	//mhZerglingBit =	new	HBITMAP[mParents[1]->GetAllImageCount()];
	//mhUltraBit =	new	HBITMAP[mParents[2]->GetAllImageCount()];
	//mhSaraBit =		new	HBITMAP[mParents[3]->GetAllImageCount()];
	mhBit = new HBITMAP*[MAX_UNIT_SPECIES];
	for (int i = 0; i < MAX_UNIT_SPECIES; i++) {
		*(mhBit + i) = nullptr;
	}
	mGameState = GAME_INIT;
}
