#ifndef __Game_End_Layer_H__
#define __Game_End_Layer_H__

#include "cocos2d.h"
USING_NS_CC;

class Game_End_Layer :public LayerColor
{
public:
	CREATE_FUNC(Game_End_Layer);
	bool init();
	
	void run_add();
	void add_callback(float t);
	void add_Score_Label();
	void add_Menu();
	int Update_Highest_Score(int value_num);
	void Play_Again_Menu_callback(Ref * ref);
	void Quit_callback(Ref * ref);

};

#endif