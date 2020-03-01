#ifndef __Bullet_Friend_H__
#define __Bullet_Friend_H__

#include "Common.h"

class Bullet_Friend:public Sprite
{
public:
	CREATE_FUNC(Bullet_Friend);
	bool init();

	void set_picture(const char * filename);
};

#endif