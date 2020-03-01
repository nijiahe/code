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
	EventListenerTouchOneByOne* mylistener = EventListenerTouchOneByOne::create();//����һ����������
	mylistener->setSwallowTouches(true);//�����Ƿ����ɴ���
	
	mylistener->onTouchBegan = [=](Touch* touch, Event* event) mutable//ָ����ʱ
	{ //[]�м���Ǵ���Ĳ���  
	  /*eventֻ��ƻ��ϵͳ������*/
	  /*typedef Vec2 Point;*//*Vec2����Point*/
		return true;//����ֵ������Ϣ�Ƿ�Ҫ�������touch����
	};

	mylistener->onTouchMoved = [=](Touch* touch, Event* event) mutable//ָ�ƶ�ʱ
	{
		CCLOG("nomove");
		
	};
	mylistener->onTouchEnded = [=](Touch* touch, Event* event) //�ɿ�ʱ
	{
		CCLOG("noended");
	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(mylistener, this);
}