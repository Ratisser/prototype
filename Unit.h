
//=================================================
//
// Unit클래스
// Unit의 생성, 행동을 결정
// 추상클래스
//
//=================================================

#ifndef _UNIT_H_
#define _UNIT_H_

#include "Vector2.h"
#include "GameFramework.h"
#include "List.h"

#define MAX_UNIT_COUNT 100

typedef enum _eUnitState {
	STOP,WATCH, MOVE, ATTACK, COLLISION
}eUnitState;

typedef enum _eUnitID {
	MARINE, ZERGLING, ULTRA, GHOST
}eUnitID;

typedef struct _Image {
	int	bitWidth;
	int	bitHeight;
	UINT transColor;
}Image;

class List;

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
	eUnitState		mUnitState;		// Unit State
	eUnitID			mUnitID;
	int				mAlliance;		// number?
	int				mUnitSize;		// Size. radius
	int				mUnitSight;		// Unit sight. radius
	int				mUnitAtkRange;	// Unit Attack Range. radius
	Unit			*mUnitAtkTarget;
	List			*mNearUnitList;

	// Unit Position
	VECTOR2			mvPos;			// Unit Position
	VECTOR2			mvDirection;	// Unit DirectionVector(normalized vector)
	VECTOR2			mvTarget;		// to move
	float			mMoveSpeed;
	int				mCollisionCount;
	int				mDegree;

	// Unit Image & Sprite
	int				*mStopSpr;
	int				*mMoveSpr;
	int				mMoveSprCount;
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
	inline void	SetTargetVector(const VECTOR2 *vTarget)	{ mvTarget.x = vTarget->x; mvTarget.y = vTarget->y; }
	inline VECTOR2 *GetPos() { return &mvPos; }
	inline VECTOR2 *GetDir() { return &mvDirection; }
	inline eUnitID GetUnitID() { return mUnitID; }
	inline eUnitState GetState() { return mUnitState; }
	inline int GetRenderTarget() { return mRenderTarget; }
	inline int GetUnitSize() { return mUnitSize; }
	inline Image *GetImgInfo() { return &mUnitImage; }
	inline int GetAlliance() { return mAlliance; }


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

//===================================
// List
//===================================
typedef struct _UnitNode {
	Unit *pUnit;
	struct _UnitNode *pNextNode;
}UnitNode;

class List
{

public:
	UnitNode *mHeadNode;
	UnitNode *mTailNode;
	UnitNode *mCurrentNode;
	int mCount;

public:
	void AddData(Unit *pUnit);
	bool DeleteData(Unit *pUnit);
	void DeleteAll();
	Unit *PeekNode();

	inline int GetListCount() { return mCount; }


public:
	List();
	~List();
};

#endif