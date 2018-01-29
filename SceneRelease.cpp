#include "stdafx.h"
#include "Game.h"

void Game::SceneRelease() {
	StarUnit::Release();
	DeleteObject(mhBackgroundBit);
	int count;

	for (int i = 0; i < MAX_UNIT_SPECIES; i++) {
		if (*(mhBit+i) != nullptr) {
			count = mpParents[i]->GetAllImageCount();
			for (int j = 0; j < count; j++) {
				if (*(*(mhBit + i) + j) != nullptr) {
					DeleteObject(*(*(mhBit + i) + j));
				}
			}
			delete[] *(mhBit + i);
		}
		delete mpParents[i];
	}
	delete[] mhBit;

}