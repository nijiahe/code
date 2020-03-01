#ifndef __enemy2_H__
#define __enemy2_H__

#include "enemy.h"

#include "cocos2d.h"
USING_NS_CC;

class enemy;

class enemy2 :public enemy
{
public:
	CREATE_FUNC(enemy2);
	bool init();
	void init_with_picture() override;
	void play_plane_boom_animation() override;
	void play_plane_injured_action() override;
	void reset_plane() override;
	void enemy_fly_action() override;
	void enemy_shoot_action(float t) override;
	void run_enemy_shoot_aciont() override;
	void init_fly_speed() override;
	void died_action()override;
};
#endif
