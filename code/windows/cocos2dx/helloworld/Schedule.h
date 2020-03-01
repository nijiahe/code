#ifndef __Schedule_H_
#define __Schedule_H_

#include"cocos2d.h"
USING_NS_CC;

/*定时器*/
class Schedule :public Layer
{
public:
	CREATE_FUNC(Schedule);//这个函数为create,调用它会调用init
							 //static MyLayer* create();
	bool init();
	static Scene* createscene();//调用这个函数来调用create
	
	void update(float dt) override;
	void myonecschedule(float dt);

};

#endif
