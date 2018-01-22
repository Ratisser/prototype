#pragma once
#include "Unit.h"
class Sara :
	public StarUnit
{
private:
	static int msprStop[];
	static int msprMove[];


protected:
	virtual void onStop();
	virtual void onMove();
public:
	virtual int GetFilePath() { return IDS_SARA_PATH; }
	virtual int GetAllImageCount() { return 51; }
	virtual int GetUnitImageCount() { return 51; }

	virtual StarUnit *GetInstance() { return new Sara; }

	Sara();
	~Sara();
};

