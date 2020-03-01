#ifndef __block_H__
#define __block_H__

#include "cocos2d.h"
USING_NS_CC;

class block :public Sprite
{
public:
	static block* create(Color3B color,Size size,Vec2 position, __String str = "",float strsize = 0,Color3B strcolor=Color3B::BLACK);
	bool init(Color3B color, Size size, Vec2 position, __String str, float strsize, Color3B strcolor = Color3B::BLACK);
	void runtouch();
	void movedown();
	void movedown_all();
};
#endif