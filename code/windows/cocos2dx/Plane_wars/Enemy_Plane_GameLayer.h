#ifndef __Enemy_Plane_GameLayer_H__
#define __Enemy_Plane_GameLayer_H__

#include "cocos2d.h"
#include "enemy.h"

USING_NS_CC;


class Enemy_Plane_GameLayer:public LayerColor
{
public:
	CREATE_FUNC(Enemy_Plane_GameLayer);
	bool init();

	void add_enemy1(float t);
	void add_enemy2(float t);
	void add_enemy3(float t);

	void run_enemy_monitor();
	void enemy_monitor_callback(float t);


	void auto_add_enemy1(float t);
	void auto_add_enemy2(float t);
	void auto_add_enemy3(float t);
	void prepare_enemy_plane_animation();
	Vector<enemy *> enemy_vector;
};

#endif