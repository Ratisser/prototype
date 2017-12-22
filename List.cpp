#include "stdafx.h"
#include "List.h"

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

void List::AddData(int data)
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

bool List::DeleteData(int data)
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

void List::DeleteAll() {
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

int List::PeekNode() {
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