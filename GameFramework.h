#ifndef _GAME_FRAME_WORK_H_
#define _GAME_FRAME_WORK_H_


#include "Vector2.h"
#define CLIENT_WIDTH 800
#define CLIENT_HEIGHT 600


typedef enum {
	LBUTTONDOWN, LBUTTONUP, RBUTTONDOWN, RBUTTONUP, MOUSE_NONE
}eMouseState;

class GameFramework
{
private:
	void fullScreenModeChange();
protected:
	HINSTANCE		mhInst;
	HWND			mhWnd;
	HDC				mhBackBuffer;
	HDC				mhdc;
	RECT			mClientRect;
	RECT			mDragRect;
	VECTOR2			mMousePoint;
	VECTOR2			mMouseSP;
	VECTOR2			mMouseEP;
	int				mDrag;
	eMouseState		mMouseState;


	int				mnFPS;
	int				mnFPSCount;
	DWORD			mdwOldTime;
	DWORD			mdwCurrentTime;
	bool			mbFullScreen;

	LARGE_INTEGER	mFrequency;
	LARGE_INTEGER	mOldTime;
	LARGE_INTEGER	mCurTime;
	LARGE_INTEGER	mOldRenderTime;
	LARGE_INTEGER	mCurRenderTime;
	LARGE_INTEGER	mElapsedTime;
	float			mDeltaTime;

protected:
	virtual void SceneInit() {}
	virtual void SceneUpdate() {}
	virtual void SceneRender() {}
	virtual void SceneRelease() {}

public:
	__forceinline static GameFramework *GetInstance() { static GameFramework singleton; return &singleton; }
	void ChangeScreenMode(BOOL bIsFullMode);

	void MouseProcess(UINT msg, LPARAM lParam);
	inline VECTOR2 GetMousePoint() { return mMousePoint; }


public:
	void Init(HINSTANCE hInst, HWND hWnd);
	void Update();
	void Render();
	void Release();



};

#endif