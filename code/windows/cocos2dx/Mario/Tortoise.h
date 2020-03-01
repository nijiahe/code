#ifndef __Tortoise_H__
#define __Tortoise_H__

#include "Common.h"
#include "Organism.h"

class Tortoise:public Organism
{
public:
	CREATE_FUNC(Tortoise);
	bool init();

	virtual void birth(Vec2 vec);
	virtual void set_picture();
	virtual void set_physics();
	virtual void set_God_physics();
	virtual void play_new_left_move_action();
	virtual void play_new_right_move_action();
	virtual void died_monitor(float t);
	virtual void start_monitor();
	virtual void stop_monitor();
	virtual void clean();
	//2代表缩进龟壳时的动作
	void auto_move2(float t);
	void relife_monitor(float t);
	void relife();

	float _now_relife_time = 0;;
	float _relife_time = 3;
};

#endif