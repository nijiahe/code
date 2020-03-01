#ifndef __rect_H__
#define __rect_H__

#include "cocos2d.h"
USING_NS_CC;

class rect :public Sprite
{
public:
	CREATE_FUNC(rect);
	bool init();
	bool ison = false;
	int num = -1;
	enum
	{
		ttflbtag,
	};
	void runtouch();
	void shownum();
	void hidenum();
	void scheduleruntouch(float dt);
	void closetouch();
	EventListenerTouchOneByOne* mylistener;
};
#endif


