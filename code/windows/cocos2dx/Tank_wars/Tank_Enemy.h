#ifndef __Tank_Enemy_H__
#define __Tank_Enemy_H__

#include "Common.h"
#include "Tank.h"

class Bullet_Enemy;

class Tank_Enemy:public Tank
{
public:
	bool init(Common::Enemy_Tank_Type type);
	static Tank_Enemy * create(Common::Enemy_Tank_Type type);
	Bullet_Enemy * shoot();
	void injured();
	int get_score();

	Common::Enemy_Tank_Type _type;
	
};

#endif

