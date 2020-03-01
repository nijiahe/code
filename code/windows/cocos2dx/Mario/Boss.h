#ifndef __Boss_H__
#define __Boss_H__

#include "Common.h"
#include "Organism.h"

class Boss :public Organism
{
public:
	CREATE_FUNC(Boss);
	bool init();

	virtual void birth(Vec2 vec);
	virtual void set_picture();
	virtual void set_physics();
	virtual void play_new_left_move_action();
	virtual void play_new_right_move_action();
	virtual void start_monitor();
	virtual void stop_monitor();
	virtual void clean();
	virtual void call_up(float t);

	virtual void died_monitor(float t);

	int _life;
	int _call_up_num = 3;
};

#endif