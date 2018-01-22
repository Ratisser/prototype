#pragma once
#include "Unit.h"


class Zergling :
	public StarUnit
{
private:
	static int msprStop[];
	static int msprMove[];

protected:
	virtual void onStop();
	virtual void onMove();
public:
	virtual int GetFilePath() { return IDS_ZERGLING_PATH; }
	virtual int GetAllImageCount() { return 296; }
	virtual int GetUnitImageCount() { return 289; }

	virtual StarUnit *GetInstance() { return new Zergling; }

	Zergling();
	~Zergling();
};
