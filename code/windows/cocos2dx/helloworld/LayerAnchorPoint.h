#ifndef __LayerAnchorPoint_H_
#define __LayerAnchorPoint_H_

#include"cocos2d.h"
USING_NS_CC;

//本质是一个Layer
class LayerAnchorPoint:public Layer
{
public:
	static LayerAnchorPoint* create();
	bool init();
	static Scene* createscene();
	Sprite* spr;
	void mySchedule(float dt);
	//void mydraw();
};

#endif

