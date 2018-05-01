
//=================================================
//
// Unit클래스
// Unit의 생성, 행동을 결정
//
//=================================================

#ifndef _UNIT_H_
#define _UNIT_H_

#include "Vector2.h"
#include "GameFramework.h"
#include <list>
using namespace std;

#define MAX_UNIT_COUNT 100

typedef enum _eUnitState {
	STOP, WATCH, MOVE, ATTACK, COLLISION
}eUnitState;

typedef enum _eUnitID {
	MARINE, ZERGLING, ULTRA, GHOST
}eUnitID;

typedef struct _Image {
	int	bitWidth;
	int	bitHeight;
	UINT transColor;
}Image;

typedef struct _Sprite {
	int				*pStopSpr;
	int				*pWatchSpr;
	int				*pMoveSpr;
	int				*pAtkSpr;
	int				watchMaxCount;
	int				moveMaxCount;
	int				atkMaxCount;
	int				animCount;
	int				renderTarget;
}Sprite;

class Unit
{
	//-----------------------------------------
	// Static variable 
	//-----------------------------------------
private:
	static Unit		*mpUnitList[MAX_UNIT_COUNT];
	static Unit		*mpUnit;
	static int		mUnitCount;

	//-----------------------------------------
	// Member variable
	//-----------------------------------------
protected:
	// Unit Attribute
	eUnitState		mUnitState;			// Unit State
	eUnitID			mUnitID;			// ID
	int				mUnitMaxHP;
	int				mUnitHP;
	int				mUnitSize;			// Size. radius
	int				mUnitSight;			// Unit sight. radius
	int				mUnitAtkRange;		// Unit Attack Range. radius
	int				mAlliance;			// number
	Unit			*mpUnitAtkTarget;

	// Unit Position
	VECTOR2			mvPos;				// Unit Position
	VECTOR2			mvDirection;		// normalized vector
	VECTOR2			mvTarget;			// to move
	float			mMoveSpeed;
	int				mCollisionCount;
	int				mDegree;
	list<VECTOR2>	mMovePath;

	// Unit Image & Sprite
	int				*mpStopSpr;
	int				*mpMoveSpr;
	int				*mpAtkSpr;
	int				mMoveSprCount;
	int				mAtkSprCount;
	int				mAtkFrame;
	int				mAnim;
	int				mRenderTarget;
	Image			mUnitImage;

	// Timer
	DWORD			mdwAnimTime;
	DWORD			mdwWaitTime;
	DWORD			mdwAktDelay;

	//-----------------------------------------
	// Static function 
	//-----------------------------------------
public:
	static void Release();
	static bool AddUnit(int i);
	static bool RemoveUnit();

	//-----------------------------------------
	// Member function
	//-----------------------------------------
protected:
	void checkRange(); // check unit range
	void onChangeState();
	void onStop();
	void onMove();
	void onAttack();

	//-----------------------------------------
	// Virtual function
	//-----------------------------------------
public:
	virtual int GetFilePath() = 0;
	virtual int GetAllImageCount() = 0;
	virtual int GetUnitImageCount() = 0;
	virtual Unit *GetInstance() = 0;

	//-----------------------------------------
	// Interface function
	//-----------------------------------------
public:
	// standard unit process
	void UnitProcess();

	// command
	void Stop();
	void Move();
	void Attack();
	void Focus();


	//-----------------------------------------
	// Getter, Setter
	//-----------------------------------------
public:
	// inline function
	inline static Unit** GetUnitList() { return mpUnitList; }
	inline static int GetUnitCount() { return mUnitCount; }

	inline void	SetPos(VECTOR2 mouse) { mvPos.x = mouse.x; mvPos.y = mouse.y; }
	inline list<VECTOR2> *GetMovePath() { return &mMovePath; }
	inline VECTOR2 *GetPos() { return &mvPos; }
	inline eUnitID GetUnitID() { return mUnitID; }
	inline eUnitState GetState() { return mUnitState; }
	inline int GetRenderTarget() { return mRenderTarget; }
	inline int GetUnitSize() { return mUnitSize; }
	inline Image *GetImgInfo() { return &mUnitImage; }
	inline int GetAlliance() { return mAlliance; }

	DEBUG_GAME(inline VECTOR2 *GetTarget() { return &mvTarget; })
	DEBUG_GAME(inline int GetAnim() { return mAnim; })

	// non-inline fuction
	void SetState(eUnitState state);
	void SetImg(int width, int height, UINT rgbColor);

	//-----------------------------------------
	// Constructor, Destructor
	//-----------------------------------------
public:
	Unit();
	~Unit();
};

#endif