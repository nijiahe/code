#ifndef __plane_H__
#define __plane_H__

#include "cocos2d.h"
USING_NS_CC;

class plane :public Sprite
{
public:
	CREATE_FUNC(plane);
	bool init();

	void play_plane_fly_animation();

	void add_life();
	void minus_life();

	void injured();
	void play_plane_injured_action();
	bool is_died();
	void died_action();
	void remove_callfunc();

	void invincible(float t);
	void invincible_action(float t);
	void un_invincible(float t);

	void reset_plane();

	bool is_invincible;
	int life_present;
	int life_max;
	enum
	{
		invincible_action_tag,
	};
};

#endif