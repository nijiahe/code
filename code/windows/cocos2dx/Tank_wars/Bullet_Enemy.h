#ifndef __Bullet_Enemy_H__
#define __Bullet_Enemy_H__

#include "Common.h"

class Bullet_Enemy:public Sprite
{
public:
	CREATE_FUNC(Bullet_Enemy);
	bool init();

	void set_picture(const char * filename);
};

#endif