#ifndef __Mario_Player
#define __Mario_Player

#include "Common.h"
#include "Organism.h"

class Mario_Player:public Organism
{
public:
	CREATE_FUNC(Mario_Player);
	bool init();
	
	virtual void birth(Vec2 vec);
	virtual void set_picture();
	virtual void set_physics();//设置小人状态的属性
	virtual void play_new_left_move_action();
	virtual void play_new_right_move_action();
	virtual void died_monitor(float t);
	void eat_coin(float t);
	virtual void run_monitor_switch();
	virtual void start_monitor();
	virtual void stop_monitor();
	virtual void clean();
	virtual void auto_move(float t) override;
	void run_automove();
	void stop_automove();

	void Top_To_Collosion_monitor(float t);
	void touch_Flagpole_monitor(float t);
	bool inspect_mushroom_reward(Sprite * spr);
	void set_eatMushroom_physics();
	void un_God_action(float t);

	bool _iseatMushroom = false;
	bool _touch_Flagpole = false;
	bool _is_died = false;
	int _God_Time = 3;
	int _coin_count = 0;
};

#endif