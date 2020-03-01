#include "bar.h"


bool bar::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	Size visible = Director::getInstance()->getWinSize(); 
	Size size = Size(rand() % 80 + visible.width*0.1, rand() % 48 + visible.height*0.1);
	this->setContentSize(size);
	this->setTextureRect(Rect(0,0,size.width,size.height));
	setAnchorPoint(Vec2(0, 0));
	setColor(Color3B(0, 0, 0));
	runschedule();
	return true;
}


void bar::runschedule()
{
	schedule(SEL_SCHEDULE(&bar::schedule_callback));
}

void bar::schedule_callback(float t)
{
	Size visible = Director::getInstance()->getWinSize();
	this->setPositionX(this->getPositionX() - visible.width*0.006);
}