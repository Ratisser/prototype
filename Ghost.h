#pragma once
#include "StarUnit.h"
class Ghost :
	public StarUnit
{
private:
	static int				msprStop[];
	static int				msprMove[];

protected:
	virtual void onStop();
	virtual void onMove();
public:
	virtual int GetFilePath() { return IDS_GHOST_PATH; }
	virtual int GetAllImageCount() { return 229; }
	virtual int GetUnitImageCount() { return 221; }

	virtual StarUnit *GetInstance() { return new Ghost; }

public:
	Ghost();
	~Ghost();
};

