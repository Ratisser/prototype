#include "stdafx.h"

#pragma comment(lib, "fmod\\fmod_vc.lib")

SoundManager::SoundManager()
{
}


SoundManager::~SoundManager()
{
}


void SoundManager::Init() {
	FMOD_System_Create(&mpSystem);
	FMOD_System_Init(mpSystem, 32, FMOD_INIT_NORMAL, NULL);

	int result;
	result = FMOD_System_CreateSound(mpSystem, "sound\\Terran.mp3", FMOD_LOOP_NORMAL, NULL, &mpBGM);
	result = FMOD_System_CreateSound(mpSystem, "sound\\TMaFir00.wav", FMOD_DEFAULT, NULL, &mpMarineFire);
}

void SoundManager::Update() {
	FMOD_System_Update(mpSystem);
}

void SoundManager::Release() {
	FMOD_Sound_Release(mpBGM);
	FMOD_Sound_Release(mpMarineFire);
	FMOD_System_Close(mpSystem);
	FMOD_System_Release(mpSystem);
}

void SoundManager::PlayBGM() {
	mpChannel = 0;
	
	FMOD_System_PlaySound(mpSystem, mpBGM, NULL, FALSE, &mpChannel);
	FMOD_Channel_SetVolume(mpChannel, 0.5f);
}

void SoundManager::PlayAtk() {
	mpChannel = 0;
	FMOD_System_PlaySound(mpSystem, mpMarineFire, NULL, FALSE, &mpChannel);
}