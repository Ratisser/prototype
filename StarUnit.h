
//=================================================
//
// Unit클래스
// Unit의 생성, 행동을 결정
// 추상클래스
//
//=================================================

#pragma once
#include "stdafx.h"
#include "Vector2.h"
#include "GameFramework.h"

#define MAX_UNIT_COUNT 100

typedef enum _UnitState {
	STOP,WATCH, MOVE, ATTACK, COLLISION
}UnitState;

typedef enum _UnitID {
	MARINE, ZERGLING, ULTRA, SARA, GHOST
}UnitID;

typedef struct _Image {
	int	bitWidth;
	int	bitHeight;
	UINT transColor;
}Image;

class StarUnit
{
	//-----------------------------------------
	// Static variable 
	//-----------------------------------------
private:
	static StarUnit		*mpUnitList[MAX_UNIT_COUNT];
	static StarUnit		*mpUnit;
	static int		mUnitCount;

	//-----------------------------------------
	// Member variable
	//-----------------------------------------
protected:
	// Unit Attribute
	UnitState		mUnitState;		// Unit State
	UnitID			mUnitID;
	int				mUnitSize;		// Size. radius
	int				mSight;			// Unit sight. radius
	int				mAtkRange;		// Unit Attack Range. radius

	// Unit Position
	VECTOR2			mvPos;			// Unit Position
	VECTOR2			mvDirection;	// Unit DirectionVector
	VECTOR2			mvTarget;		// to move
	float			mMoveSpeed;
	int				mCollisionCount;
	int				mDegree;

	// Unit Image & Sprite
	int				mAnim;
	int				mRenderTarget;
	Image			mUnitImage;

	// Timer
	DWORD			mdwAnimTime;
	DWORD			mdwWaitTime;

	//-----------------------------------------
	// Static function 
	//-----------------------------------------
public:

	//-----------------------------------------
	// Member function
	//-----------------------------------------
protected:
	void checkRange(); // check unit range
	void onChangeState();

	//-----------------------------------------
	// Virtual function
	//-----------------------------------------
protected:
	virtual void onStop() {};
	virtual void onMove() = 0;
public:
	virtual int GetFilePath() = 0;
	virtual int GetAllImageCount() = 0;
	virtual int GetUnitImageCount() = 0;
	virtual StarUnit *GetInstance() = 0;

	//-----------------------------------------
	// Interface function
	//-----------------------------------------
public:
	// standard unit process
	void UnitProcess();

	// get baby
	static bool AddUnit(int i);
	static bool RemoveUnit();

	// command
	void Stop();
	void Move();
	void Attack();
	void Focus();

	static void Release();

	//-----------------------------------------
	// Getter, Setter
	//-----------------------------------------
public:
	// inline function
	inline static StarUnit** GetUnitList() { return mpUnitList; }
	inline static int GetUnitCount() { return mUnitCount; }

	inline void	SetPos(VECTOR2 mouse) { mvPos.x = mouse.x; mvPos.y = mouse.y; }
	inline void	SetTargetVector(const VECTOR2 *vTarget)	{ mvTarget.x = vTarget->x; mvTarget.y = vTarget->y; }
	inline VECTOR2 *GetPos() { return &mvPos; }
	inline VECTOR2 *GetDir() { return &mvDirection; }
	inline UnitID GetUnitID() { return mUnitID; }
	inline UnitState GetState() { return mUnitState; }
	inline int GetRenderTarget() { return mRenderTarget; }
	inline int GetUnitSize() { return mUnitSize; }
	inline Image *GetImgInfo() { return &mUnitImage; }


	// non-inline fuction
	void SetState(UnitState state);
	void SetImg(int width, int height, UINT rgbColor);

	//-----------------------------------------
	// Constructor, Destructor
	//-----------------------------------------
public:
	StarUnit();
	~StarUnit();
};
