#ifndef __MyScene_h_
#define __MyScene_h_

#include"cocos2d.h"
USING_NS_CC;

class MyScene :public Scene
{
public:
	CREATE_FUNC(MyScene);//调用这个函数的时候会调用init
	bool init();
};

#endif
