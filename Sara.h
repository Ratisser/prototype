#pragma once
#include "Unit.h"
class Sara :
	public Unit
{
private:
	static const int UNIT_IMAGE_COUNT;
	static const int TOTAL_IMAGE_COUNT;
	static int msprStop[];
	static int msprMove[];


protected:
	virtual void onStop();
	virtual void onMove();
public:
	inline static int GetAllImageCount() { return TOTAL_IMAGE_COUNT; }
	inline static int GetUnitImageCount() { return UNIT_IMAGE_COUNT; }

	Sara();
	~Sara();
};

