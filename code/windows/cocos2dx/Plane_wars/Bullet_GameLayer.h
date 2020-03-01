#ifndef __Bullet_GameLayer_H__
#define __Bullet_GameLayer_H__

#include "Bullet1.h"
#include "cocos2d.h"
USING_NS_CC;

class Bullon1;

class Bullet_GameLayer :public LayerColor
{
public:
	CREATE_FUNC(Bullet_GameLayer);
	bool init();

	void prepare_bullet_batchnode();
	void produce_bullet(float t);
	void bullet_run(Sprite * bullet);
	void start_shoot(float shoot_rate);
	void stop_shoot();
	void run_remove_bullet_schedule();
	void remove_bullet_schedule_callback(float t);


	SpriteBatchNode * bullet_batchnode;
	Vector<Bullet1*> bullet_vector;
	float bullet_speed = 400;
};

#endif

