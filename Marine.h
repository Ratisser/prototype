#ifndef _MARINE_H_
#define _MARINE_H_

#include "Unit.h"

class Marine :
	public Unit
{
private:
	static int msprStop[];
	static int msprMove[];
	static int msprAttack[];

public:
	virtual int GetFilePath() { return IDS_MARINE_PATH; }
	virtual int GetAllImageCount() { return 229; }
	virtual int GetUnitImageCount() { return 221; }

	virtual Unit *GetInstance() { return new Marine; }

	Marine();
	~Marine();
};

#endif