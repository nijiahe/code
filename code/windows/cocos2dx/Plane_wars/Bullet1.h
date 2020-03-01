#ifndef __Bullet1_H__
#define __Bullet1_H__

#include "cocos2d.h"
USING_NS_CC;

class Bullet1 :public Sprite
{
public:
	CREATE_FUNC(Bullet1);
	bool init();

	bool out_of_visible();
	bool is_hit_enemy();
};

#endif