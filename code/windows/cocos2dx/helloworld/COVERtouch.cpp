#include "COVERtouch.h"

bool COVERtouch::init()
{
	if (!LayerColor::initWithColor(Color4B(0, 255, 255, 255)))
	{
		return false;
	}
	Runtouch();


	return true;
}

void COVERtouch::Runtouch()
{
	EventListenerTouchOneByOne* mylistener = EventListenerTouchOneByOne::create();//创建一个触摸监听
	mylistener->setSwallowTouches(true);//设置是否吞噬触摸
	
	mylistener->onTouchBegan = [=](Touch* touch, Event* event) mutable//指按下时
	{ //[]中间的是传入的参数  
	  /*event只在苹果系统上有用*/
	  /*typedef Vec2 Point;*//*Vec2就是Point*/
		return true;//返回值决定消息是否要发到别的touch函数
	};

	mylistener->onTouchMoved = [=](Touch* touch, Event* event) mutable//指移动时
	{
		CCLOG("nomove");
		
	};
	mylistener->onTouchEnded = [=](Touch* touch, Event* event) //松开时
	{
		CCLOG("noended");
	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(mylistener, this);
}