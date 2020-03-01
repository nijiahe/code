#ifndef __Ladder_Base_H__
#define __Ladder_Base_H__

#include "Common.h"
#include "Organism.h"

class Ladder_Base :public Organism
{
public:
	CREATE_FUNC(Ladder_Base);
	bool init();

	virtual void birth(Vec2 vec);
	virtual void set_picture();
	virtual void set_physics();
	virtual void play_new_left_move_action();
	virtual void play_new_right_move_action();
	virtual void auto_move(float t);
	virtual void died_monitor(float t);
	virtual void start_monitor();
	virtual void stop_monitor();
	virtual void clean();

	int _horizontal = 0;
	int _horizontal_max;//Ïò×ó¼õÏòÓÒ¼Ó
	int _horizontal_min;
	int _height = 0;
	int _height_max;
	int _height_min;
	bool _is_down = false;
};

#endif