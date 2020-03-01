#ifndef __Plane_GameLayer_H__
#define __Plane_GameLayer_H__

#include "cocos2d.h"

class plane;

USING_NS_CC;

class Plane_GameLayer :public LayerColor
{
public:
	CREATE_FUNC(Plane_GameLayer);
	bool init();
	void add_plane();

	void prepare_plane_animation();

	EventListenerTouchOneByOne* mylistener;
	void runtouch();
	void closetouch();

	plane * _plane;
};

#endif