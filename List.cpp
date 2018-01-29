#include "stdafx.h"


List::List()
{
	mHeadNode = nullptr;
	mTailNode = nullptr;
	mCurrentNode = nullptr;
	mCount = 0;
}


List::~List()
{

}

void List::AddData(Unit *pUnit)
{
	if (mHeadNode == nullptr)
	{
		mHeadNode = new UnitNode;
		mHeadNode->pNextNode = mHeadNode;
		mHeadNode->pUnit = pUnit;
		mTailNode = mHeadNode;
		mCount++;
	}
	else
	{
		mTailNode->pNextNode = new UnitNode;
		mTailNode = mTailNode->pNextNode;
		mTailNode->pNextNode = mHeadNode;
		mTailNode->pUnit = pUnit;
		mCount++;
	}
}

bool List::DeleteData(Unit *pUnit)
{
	if (mHeadNode == nullptr) return false;
	UnitNode *prevNode = mTailNode;
	UnitNode *currentNode = mHeadNode;
	do {
		if (currentNode->pUnit == pUnit) {
			prevNode->pNextNode = currentNode->pNextNode;
			delete currentNode;
			mCount--;
			return true;
		}
		else {
			currentNode = currentNode->pNextNode;
			prevNode = prevNode->pNextNode;
		}
	} while (currentNode != mHeadNode);
	return false;

}

void List::DeleteAll() {
	if (mHeadNode == nullptr) return;
	UnitNode *currentNode = mHeadNode;
	UnitNode *deleteNode = currentNode;

	for (int i = 0; i < mCount; i++) {
		currentNode = currentNode->pNextNode;
		delete deleteNode;
		deleteNode = currentNode;
	}
	mHeadNode = nullptr;
	mTailNode = nullptr;
	mCurrentNode = nullptr;
	mCount = 0;
}

Unit *List::PeekNode() {
	Unit *returnVar;
	if (mHeadNode == nullptr)
	{
		return nullptr;
	}
	else
	{
		if (mCurrentNode == nullptr) {
			mCurrentNode = mHeadNode;
		}
		returnVar = mCurrentNode->pUnit;
		mCurrentNode = mCurrentNode->pNextNode;
	}
	return returnVar;
}