#include "stdafx.h"
#include "Game.h"

void Game::SceneRelease() {
	StarUnit::Release();
	DeleteObject(mhBackgroundBit);


	for (int i = 0; i < MAX_UNIT_SPECIES; i++) {
		for (int j = 0; j < mpParents[i]->GetAllImageCount(); j++) {
			DeleteObject(*(*(mhBit+i)+j));
		}
		delete mpParents[i];
		delete[] *(mhBit + i);
	}
	delete[] mhBit;
	
}