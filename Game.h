#pragma once
#include "GameFramework.h"
#include "StarUnit.h"
#include "Vector2.h"

#pragma warning(disable:4996)
#pragma comment(lib, "msimg32.lib")

#define MAX_UNIT_SPECIES 5

typedef enum {
	GAME_INIT, GAME_TITLE, GAME_ROOP, GAME_DESTROY
}eGameState;

// �������� ����ó���� �ϴ� Ŭ����
class Game :
	public GameFramework
{
	//-----------------------------------------
	// Static variable 
	//-----------------------------------------
public:
	static StarUnit *mpParents[];

	//-----------------------------------------
	// member variable 
	//-----------------------------------------
private:
	// �ð��� ����
	DWORD mOldTime;
	DWORD mCurrentTime;
	eGameState mGameState;

	// ����� ���ڿ���
	TCHAR mFPS[50];
	TCHAR mUnitCount[50];
	TCHAR mSystemMsg[50];
	TCHAR mFileName[50];
	TCHAR mFilePath[50];

	//--------------------
	// �̹��� ������ DC �ڵ�
	//--------------------
	HBITMAP **mhBit;
	HBITMAP mhBackgroundBit;
	
	StarUnit *mSelectedUnit[12];
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
	void ClearSelectedUnit();

	HBITMAP CreateBitmapDC(LPCWSTR filename);
	HBITMAP CreateReverseDC(LPCWSTR filename);

	// �ӽ�...
	HWND hList;

	Game();
	~Game();
};

