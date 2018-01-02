#include "stdafx.h"
#include "List.h"

LinkedList::LinkedList()
{
	mHeadNode = nullptr;
	mTailNode = nullptr;
	mCurrentNode = nullptr;
	mCount = 0;
}


LinkedList::~LinkedList()
{

}

void LinkedList::AddData(int data)
{
	if (mHeadNode == nullptr)
	{
		mHeadNode = new UnitNode;
		mHeadNode->nextNode = mHeadNode;
		mHeadNode->data = data;
		mTailNode = mHeadNode;
		mCount++;
	}
	else
	{
		mTailNode->nextNode = new UnitNode;
		mTailNode = mTailNode->nextNode;
		mTailNode->nextNode = mHeadNode;
		mTailNode->data = data;
		mCount++;
	}
}

bool LinkedList::DeleteData(int data)
{
	if (mHeadNode == nullptr) return false;
	UnitNode *prevNode = mTailNode;
	UnitNode *currentNode = mHeadNode;
	do {
		if (currentNode->data == data) {
			prevNode->nextNode = currentNode->nextNode;
			delete currentNode;
			return true;
		}
		else {
			currentNode = currentNode->nextNode;
			prevNode = prevNode->nextNode;
		}
	} while (currentNode != mHeadNode);
	return false;

}

void LinkedList::DeleteAll() {
	if (mHeadNode == nullptr) return;
	UnitNode *currentNode = mHeadNode;
	UnitNode *deleteNode = currentNode;

	for (int i = 0; i < mCount; i++) {
		currentNode = currentNode->nextNode;
		delete deleteNode;
		deleteNode = currentNode;
	}
	mHeadNode = nullptr;
	mTailNode = nullptr;
	mCurrentNode = nullptr;
}

int LinkedList::PeekNode() {
	int returnVar;
	if (mHeadNode == nullptr)
	{
		return -1;
	}
	else
	{
		if (mCurrentNode == nullptr) {
			mCurrentNode = mHeadNode;
		}
		returnVar = mCurrentNode->data;
		mCurrentNode = mCurrentNode->nextNode;
	}
	return returnVar;
}