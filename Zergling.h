#ifndef _ZERGLING_H_
#define _ZERGLING_H_

#include "Unit.h"


class Zergling :
	public Unit
{
private:
	static int msprStop[];
	static int msprMove[];

public:
	virtual int GetFilePath() { return IDS_ZERGLING_PATH; }
	virtual int GetAllImageCount() { return 296; }
	virtual int GetUnitImageCount() { return 289; }

	virtual Unit *GetInstance() { return new Zergling; }

	Zergling();
	~Zergling();
};

#endif