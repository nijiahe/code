#ifndef __Tank_H__
#define __Tank_H__

#include "Common.h"

class Tank:public Sprite
{
public:
	bool init();
	CREATE_FUNC(Tank);

	void turn(Common::Dir_Control dir);
	void move();
	void set_picture(const char* filename);
	bool canmove();
	void physics_init(int life, int file_power, float speed);

	
	int _life = 3;
	int _file_power = 0;
	float _speed = 2;
	Common::Dir_Control _dir = Common::Dir_Control::Up;

};

#endif