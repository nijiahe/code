#ifndef __Mushroom_Reward_H__
#define __Mushroom_Reward_H__

#include "Common.h"
#include "Organism.h"

class Mushroom_Reward :public Organism
{
public:
	CREATE_FUNC(Mushroom_Reward);
	bool init();

	virtual void birth(Vec2 vec);
	virtual void set_picture();
	virtual void set_physics();
	virtual void play_new_left_move_action();
	virtual void play_new_right_move_action();
	virtual void died_monitor(float t);
	virtual void start_monitor();
	virtual void stop_monitor();
	virtual void clean();
	virtual void auto_move(float t);

	void start_monitor_switch();

	void wakeup();

	bool _Sleep = true;
};

#endif