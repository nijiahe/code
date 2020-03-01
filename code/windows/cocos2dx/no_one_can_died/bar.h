#ifndef __bar_H_
#define __bar_H_

#include "cocos2d.h"
USING_NS_CC;

class bar :public Sprite
{
public:
	CREATE_FUNC(bar);
	static Scene * createscene();
	bool init();

	void runschedule();
	void schedule_callback(float t);
};
#endif

