#pragma once
#include "Unit.h"

class Ultra :
	public StarUnit
{
private:
	static int msprStop[];
	static int msprMove[];


protected:
	virtual void onStop();
	virtual void onMove();
public:
	virtual int GetFilePath() { return IDS_ULTRA_PATH; }
	virtual int GetAllImageCount() { return 265; }
	virtual int GetUnitImageCount() { return 255; }

	virtual StarUnit *GetInstance() { return new Ultra; }

	Ultra();
	~Ultra();
};
