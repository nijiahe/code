#ifndef __enemy_H__
#define __enemy_H__

#include "cocos2d.h"

USING_NS_CC;


class enemy :public Sprite
{
public:
	CREATE_FUNC(enemy);
	bool init();
	virtual void init_with_picture();
	virtual void play_plane_boom_animation();
	virtual void play_plane_injured_action();
	virtual void reset_plane();
	virtual void enemy_fly_action();
	virtual void enemy_shoot_action(float t);
	virtual void run_enemy_shoot_aciont();
	virtual void init_fly_speed();
	virtual void died_action();


	void minus_life();
	void injured();
	bool is_hited();
	bool is_died();
	bool is_impact_with_hero();
	bool is_out_more_of_visible();
	void remove_callback();

	int life_present;
	int life_max;
	float fly_speed;
};

#endif