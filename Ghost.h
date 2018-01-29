#ifndef _GHOST_H_
#define _GHOST_H_

#include "Unit.h"

class Ghost :
	public Unit
{
private:
	static int				msprStop[];
	static int				msprMove[];

public:
	virtual int GetFilePath() { return IDS_GHOST_PATH; }
	virtual int GetAllImageCount() { return 229; }
	virtual int GetUnitImageCount() { return 221; }

	virtual Unit *GetInstance() { return new Ghost; }

	Ghost();
	~Ghost();
};

#endif