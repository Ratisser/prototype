#pragma once
#include "GameFrame.h"
#include "Unit.h"

// 실질적인 게임처리는 여기서

typedef enum {
	GAME_INIT, GAME_TITLE, GAME_ROOP, GAME_DESTROY
}eGameState;

class Game :
	public GameFrame
{
private:
	DWORD mOldTime;
	DWORD mCurrentTime;
	eGameState mGameState;

	TCHAR mFPS[50];
	TCHAR mUnitCount[50];
	TCHAR mSystemMsg[50];
	TCHAR mFileName[50];

	//--------------------
	// 이미지 저장할 HDC
	//--------------------
	HDC *mhMarineDC;
	HDC *mhZerglingDC;
	HDC *mhUltraDC;
	HDC *mhSaraDC;
	HDC mhBackgroundDC;
	
	Unit *mSelectedUnit[12];
	int mSelectedCount;

protected:
	virtual void SceneInit();
	virtual void SceneUpdate();
	virtual void SceneRender();
	virtual void SceneRelease();
public:
	__forceinline static Game *GetInstance() { static Game singleton; return &singleton; }
	__forceinline DWORD GetTime() { return mCurrentTime; }

	void ErrorFileLoad();

	HDC CreateBitmapDC(LPCWSTR filename);
	HDC CreateReverseDC(LPCWSTR filename);

	HWND hList;

	Game();
	~Game();
};

