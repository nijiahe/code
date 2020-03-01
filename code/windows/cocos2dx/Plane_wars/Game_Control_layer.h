#ifndef __Game_Control_layer_H__
#define __Game_Control_layer_H__

#include "cocos2d.h"

class plane;

USING_NS_CC;

class Game_Control_layer :public LayerColor
{
public:
	CREATE_FUNC(Game_Control_layer);
	bool init();

	void add_Score_Label();
	void add_Pause_Menu();
	void add_Plane_life_visible();
	void Update_Plane_life_visible();
	void add_Bomb_Menu();
	void add_Bomb_Count_visible();
	void Update_Bomb_Count_visible();
	void use_Bomb();
	void Bomb_Menu_callback();
	void Pause_And_Continue_Menu_callback(Ref * ref);
	void Update_Score(int num);
	
	enum
	{
		pause_item_tag,
		continue_item_tag,
	};

	int score = 0;
	MenuItemToggle* Pause_Menu_Toogle;
	Label * Score_Lalel;
	Label * Plane_Life;
};

#endif