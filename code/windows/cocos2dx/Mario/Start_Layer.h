#ifndef __Start_Layer_H__
#define __Start_Layer_H__

#include "Common.h"


class Start_Layer:public Layer
{
public:
	CREATE_FUNC(Start_Layer);
	bool init();

	void startgame_item_callback(Ref * ref);
	void seting_item_callback(Ref * ref);
	void quitgame_item_callback(Ref * ref);
	void about_item_callback(Ref * ref);
};

#endif