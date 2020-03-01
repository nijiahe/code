#ifndef __Bullet2_H__
#define __Bullet2_H__

#include "cocos2d.h"
USING_NS_CC;

class Bullet2 :public Sprite
{
public:
	CREATE_FUNC(Bullet2);
	bool init();

	bool out_of_visible();
	bool is_hit_plane();
};

#endif