#ifndef __MenuCtl_H_
#define __MenuCtl_H_

#include "Common.h"

class MenuCtl:public Menu
{
public:
	CREATE_FUNC(MenuCtl);
	bool init();

	void schedule_callback(float t);
};

#endif