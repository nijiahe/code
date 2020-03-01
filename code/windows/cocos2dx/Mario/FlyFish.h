#ifndef __FlyFish_H__
#define __FlyFish_H__

#include "Common.h"
#include "Organism.h"

class FlyFish:public Organism
{
public:
	CREATE_FUNC(FlyFish);
	bool init();

	virtual void birth(Vec2 vec);
	virtual void set_picture();
	virtual void set_physics();
	virtual void play_new_left_move_action();
	virtual void play_new_right_move_action();
	virtual void auto_move(float t);
	virtual void jump_monitor(float t);
	virtual void change_speed_monitor(float t);
	virtual void start_monitor();
	virtual void stop_monitor();
	virtual void clean();
	
	void unset_rest(float t);
	void wake_up(float t);
	void sleep(float t);

	int _color_type;
	float _height = 0;
	float _max_height;
	bool _is_down = false;
	float _origin_left_right_move_power;//原来的左右移动力量
	float _origin_jump_power;//原来的弹跳力
	bool _rest = false;
	bool _is_sleep = true;

};

#endif