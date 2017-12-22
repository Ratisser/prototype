#pragma once

typedef struct _UnitNode {
	int data;
	_UnitNode *nextNode;
}UnitNode;

class List
{
private:
	UnitNode *mHeadNode;
	UnitNode *mTailNode;
	UnitNode *mCurrentNode;
	int mCount;

public:
	void AddData(int data);
	bool DeleteData(int data);
	void DeleteAll();
	int PeekNode();
	
	inline int GetListCount() { return mCount; }


public:
	List();
	~List();
};