#include <stdio.h>

#include "stdafx.h"
#include "Game.h"


//-----------------------------------------------
// ����� ���۵Ǳ� �� �ʱ�ȭ �۾��� �մϴ�.
// �߰� �ʱ�ȭ �۾��� SceneUpdate���� �մϴ�.
//-----------------------------------------------
void Game::SceneInit()
{
	// �̹��� DC���� �޸� �Ҵ�
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
