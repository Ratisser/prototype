#ifndef _ULTRA_H_
#define _ULTRA_H_

#include "Unit.h"

class Ultra :
	public Unit
{
private:
	static int msprStop[];
	static int msprMove[];

public:
	virtual int GetFilePath() { return IDS_ULTRA_PATH; }
	virtual int GetAllImageCount() { return 265; }
	virtual int GetUnitImageCount() { return 255; }

	virtual Unit *GetInstance() { return new Ultra; }

	Ultra();
	~Ultra();
};

#endif