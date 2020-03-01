#ifndef __Game_layer_H_
#define __Game_layer_H_

#include "cocos2d.h"
#include "bar.h"
USING_NS_CC;

class Game_layer :public LayerColor
{
public:
	CREATE_FUNC(Game_layer);
	static Scene * createscene();
	bool init();
	enum
	{
		herotag, 
		floortag,
	};

	void add_floor();
	void add_people();
	void add_bar();
	void reset_bar();
	void runschedule();
	void schedule_callback(float t);
	void runtouch();
	void hero_land_schedule_callback(float t);
	bool is_hero_standon_something();
	bool is_hero_standon_bar();
	void run_hero_standon_schedule(float t);

	Vector<bar *> bar_vector;
	int bar_Completion;
	int bar_threshold;
	bool  stand_on_thing = true;
};
#endif

