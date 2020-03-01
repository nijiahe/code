#ifndef __MyLayer_h_
#define __MyLayer_h_

#include"cocos2d.h"
USING_NS_CC;

class MyLayer :public LayerColor
{
public:
	CREATE_FUNC(MyLayer);//这个函数为create,调用它会调用init
	//static MyLayer* create();
	bool init();
	static Scene* createscene();//调用这个函数来调用create
};

#endif
