#ifndef __Tank_Friends_H__
#define __Tank_Friends_H__

#include "Common.h"
#include "Tank.h"

class Bullet_Friend;

class Tank_Friends:public Tank
{
public:
	bool init();
	CREATE_FUNC(Tank_Friends);
	void turn(Common::Dir_Control dir);
	void move();
	bool canmove();
	Bullet_Friend * shoot();
	void injured(int time);
	void safe_top_schedule(float t);
	void shoot_schedule(float t);

	int _life = 3;
	int _file_power = 1;
	float _speed = 2;
	Common::Dir_Control _dir = Common::Dir_Control::Up;
	bool _safe_top = false;
	bool _can_shoot = true;
	int _score = 0;
};

#endif