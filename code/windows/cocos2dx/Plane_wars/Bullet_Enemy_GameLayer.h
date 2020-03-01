#ifndef __Bullet_Enemy_GameLayer_H__
#define __Bullet_Enemy_GameLayer_H__

#include "Bullet2.h"

#include "cocos2d.h"
USING_NS_CC;


class Bullet_Enemy_GameLayer :public LayerColor
{
public:
	CREATE_FUNC(Bullet_Enemy_GameLayer);
	bool init();

	void add_bullet(Bullet2 * bullet);
	void run_remove_bullet_schedule();
	void remove_bullet_schedule_callback(float t);


	SpriteBatchNode * bullet_batchnode;
	Vector<Bullet2 *> bullet_vector;
	float bullet_speed = 250;
};

#endif

