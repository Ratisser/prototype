#pragma once
#include "Vector2.h"
#define CLIENT_WIDTH 800
#define CLIENT_HEIGHT 600


typedef enum {
	LBUTTONDOWN, LBUTTONUP, RBUTTONDOWN, RBUTTONUP, MOUSE_NONE
}eMouseState;

class GameFrame
{
private:
	void fullScreenModeChange();
protected:
	HWND mhWnd;
	HDC mhBackBuffer;
	HDC mhdc;
	RECT mClientRect;
	VECTOR2 mMousePoint;
	eMouseState mMouseState;

	int mnFPS;
	int mnFPSCount;
	DWORD mdwOldTime;
	DWORD mdwCurrentTime;
	float mdwCurRenderTime;
	float mdwOldRenderTime;
	bool mbFullScreen;

protected:
	virtual void SceneInit() {}
	virtual void SceneUpdate() {}
	virtual void SceneRender() {}
	virtual void SceneRelease() {}

public:
	__forceinline static GameFrame *GetInstance() { static GameFrame singleton; return &singleton; }
	void ChangeScreenMode(BOOL bIsFullMode);

	void MouseProcess(UINT msg, LPARAM lParam);
	inline VECTOR2 GetMousePoint() { return mMousePoint; }


public:
	void Init(HWND hWnd);
	void Update();
	void Render();
	void Release();



};