#pragma once
#include "Unit.h"

class Marine :
	public StarUnit
{
private:
	static int				msprStop[];
	static int				msprMove[];

protected:
	virtual void onStop();
	virtual void onMove();
public:
	virtual int GetFilePath() { return IDS_MARINE_PATH; }
	virtual int GetAllImageCount() { return 229; }
	virtual int GetUnitImageCount() { return 221; }

	virtual StarUnit *GetInstance() { return new Marine; }

	Marine();
	~Marine();
};
