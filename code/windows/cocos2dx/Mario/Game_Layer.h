#ifndef __Game_Layer_H__
#define __Game_Layer_H__

#include "Common.h"

class Mario_Player;
class Organism;
class Tortoise;
class MenuCtl;
class Mushroom_Reward;
class Ladder_Base;

class Game_Layer:public Layer
{
public:
	static Game_Layer * create(int idx, Mario_Player * mario);
	bool init(int idx, Mario_Player * mario);
	void add_ctl();
	void add_objGroup();
	void move_left_menu_callback(Ref * ref);
	void move_right_menu_callback(Ref * ref);
	void jump_menu_callback(Ref * ref);
	void mario_move_schedule_callback(float t);
	void gravitation_schedule_callback(float t);
	void mario_WIN_AND_LOST_schedule_callback(float t);
	void coin_visible_schedule_callback(float t);
	void action1(float t);
	void action2(float t);
	void touch_finalpoint(float t);
	void replace_Scene_schedule(float t);
	void goto_next_Ground(float t);
#ifdef WIN32
	void keyboard_monitor(float t);
#endif

	Vector<Organism *> _gravitation_vec;
	Vector<Organism *> _organism_vec;
	Vector<Mushroom_Reward *> _reward_vec;
	Vector<Organism *> _enemy_vec;
	Vector<Tortoise *> _tortoise_vec;
	Vector<Ladder_Base *> _labber_vec;
	
	float _gravity = 20;
	float _air_resistance = 0.02f;

	TMXTiledMap * _map;
	Sprite * _dir_control;
	MenuCtl * _menuctl;
	LabelAtlas * _coin_count;

	Mario_Player * _mario;
	int _idx;
	Sprite * _flag;
	Sprite * _finalpoint;

};

#endif