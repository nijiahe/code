#ifndef __MenuCtl_H__
#define __MenuCtl_H__

#include "Common.h"

class MenuCtl:public Menu
{
public:
	bool init();
	CREATE_FUNC(MenuCtl);

	void schedule_callfunc(float t);
};

#endif