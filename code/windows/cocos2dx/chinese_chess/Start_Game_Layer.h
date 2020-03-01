#ifndef __Start_Game_Layer_H__
#define __Start_Game_Layer_H__

#include "cocos2d.h"
USING_NS_CC;

class Start_Game_Layer:public LayerColor
{
public:
	CREATE_FUNC(Start_Game_Layer);
	bool init();
	static Scene * createscene();

	void add_background();
	void add_menu();
	void play_with_ai_menu_callfunc(Ref * ref);
	void paly_with_player_menu_callfunc(Ref * ref);
	void quit_menu_callfunc(Ref * ref);
};

#endif