
//=================================================
//
// Unit클래스
// Unit의 생성, 행동을 결정
// 추상클래스
//
//=================================================

#pragma once
#include "Vector2.h"
#include "GameFrame.h"

#define MAX_UNIT_COUNT 100

typedef enum _UnitState {
	STOP,WATCH, MOVE, ATTACK, COLLISION
}UnitState;

typedef enum _UnitID {
	MARINE, ZERGLING, ULTRA
}UnitID;



class Unit
{
	//-----------------------------------------
	// Static variable 
	//-----------------------------------------
private:
	static Unit *mpUnitList[MAX_UNIT_COUNT];
	static Unit *mpUnit;
	static int mUnitCount;
	
	//-----------------------------------------
	// Member variable
	//-----------------------------------------
protected:
	UnitState mUnitState; // Unit State
	int mUnitSize; // Size be radius
	int mRange; // Unit range must be radius

	VECTOR2 mPos; // Unit Position
	VECTOR2 mDirection; // Unit DirectionVector
	VECTOR2 *mTarget; // Unit gaze at POINT 타겟인 유닛이 없을 경우 and 명령이 내려왔을 경우 변경
	VECTOR2 mvTarget;
	float mMoveSpeed; // Unit speed == 방향벡터에 곱할 값
	int mDegree;


	UnitID mUnitID;
	int mBitmapSize;

	DWORD mdwAnimTime;
	int mAnim;
	int mRenderTarget;
	int *mSprite;

	//-----------------------------------------
	// Virtual function
	//-----------------------------------------
protected:
	virtual void onStop() {};
	virtual void onMove() = 0;

	//-----------------------------------------
	// Member function
	//-----------------------------------------
protected:
	void checkRange(); // check unit range
	void onChangeState();

	//-----------------------------------------
	// Interface
	//-----------------------------------------
public:
	// standard unit process
	void UnitProcess();

	// make parent. get baby
	static bool AddUnit(int i);

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
	inline void SetPos(VECTOR2 mouse) { mPos.x = mouse.x; mPos.y = mouse.y; }
	inline void SetTargetVector(const VECTOR2 *vTarget) { mvTarget.x = vTarget->x;mvTarget.y = vTarget->y; }
	inline VECTOR2 *GetPos() { return &mPos; }
	inline VECTOR2 *GetDir() { return &mDirection; }
	inline static Unit** GetUnitList() { return mpUnitList; }
	inline static int GetUnitCount() { return mUnitCount; }
	inline UnitID GetUnitID() { return mUnitID; }
	inline UnitState GetState() { return mUnitState; }
	inline int GetRenderTarget() { return mRenderTarget; }
	inline void ChangeAnim() { mAnim++; }


	inline int GetBitmapSize() { return mBitmapSize; }

	void SetState(UnitState state);
	
	//-----------------------------------------
	// Constructor, Destructor
	//-----------------------------------------
public:
	Unit();
	~Unit();
};
