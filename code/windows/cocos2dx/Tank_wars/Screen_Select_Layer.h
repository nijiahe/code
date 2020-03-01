#ifndef __Screen_Select_Layer_H__
#define __Screen_Select_Layer_H__


#include "Common.h"


class Screen_Select_Layer :public Layer
{
public:
	bool init();
	CREATE_FUNC(Screen_Select_Layer);

	void toogle_callfunc(Ref * ref);
	void go_callfunc(Ref * ref);

	int _toogle_index = 0;

	
};

#endif