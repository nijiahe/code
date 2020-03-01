#ifndef __Start_Layer_H__
#define __Start_Layer_H__


#include "Common.h"


class Start_Layer:public Layer
{
public:
	bool init();
	CREATE_FUNC(Start_Layer);

	void start_game_menu_callfunc(Ref * ref);
	void load_source();

	
};

#endif