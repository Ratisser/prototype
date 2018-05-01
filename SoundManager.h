#ifndef _SOUND_MANAGER_H_
#define _SOUND_MANAGER_H_

#include "fmod\fmod.h"

class SoundManager
{
private:
	FMOD_SYSTEM *mpSystem;
	FMOD_SOUND *mpBGM;
	FMOD_SOUND *mpMarineFire;
	FMOD_CHANNEL *mpChannel;

public:
	__forceinline static SoundManager *GetInstance() { static SoundManager singleton; return &singleton; }

	void Init();
	void Update();
	void Release();

	void PlayBGM();
	void PlayAtk();

	SoundManager();
	~SoundManager();
};

#endif