#ifndef __MyLayer_h_
#define __MyLayer_h_

#include"cocos2d.h"
USING_NS_CC;

class MyLayer :public LayerColor
{
public:
	CREATE_FUNC(MyLayer);//�������Ϊcreate,�����������init
	//static MyLayer* create();
	bool init();
	static Scene* createscene();//�����������������create
};

#endif
