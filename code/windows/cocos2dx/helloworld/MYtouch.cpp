#include "MYtouch.h"
#include "COVERtouch.h"

bool MYtouch::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}
	Size visible = Director::getInstance()->getWinSize();

	Sprite* bullet = Sprite::create("bullet.png");
	bullet->setPosition(Vec2(visible.width / 4, visible.height / 4));
	//bullet->setAnchorPoint(Vec2(0, 0));
	this->addChild(bullet);
	bullet->setTag(BULLET);

	Runtouch();
	return true;
}

Scene* MYtouch::createscene()
{
	Scene* scene = Scene::create();
	COVERtouch* nolayer = COVERtouch::create();
	scene->addChild(nolayer, 99);

	MYtouch* layer = MYtouch::create();
	scene->addChild(layer,100);
	
	return scene;
}

void MYtouch::Runtouch()
{
	Size visible = Director::getInstance()->getWinSize();
	Sprite* bullet = dynamic_cast<Sprite*>(getChildByTag(BULLET));//子类父类转化

	EventListenerTouchOneByOne* mylistener = EventListenerTouchOneByOne::create();//创建一个触摸监听
	Rect rect = Rect(0, 0, visible.width, visible.height);//设置触摸区域
	mylistener->setSwallowTouches(true);//设置是否吞噬触摸
	Vec2 realpt = bullet->getPosition();
	mylistener->onTouchBegan = [=](Touch* touch, Event* event) mutable//指按下时
	{ //[]中间的是传入的参数  
	  /*event只在苹果系统上有用*/
	  /*typedef Vec2 Point;*//*Vec2就是Point*/
		Vec2 pt = touch->getLocation();
		CCLOG("TouchBegan:realpt.x=%g,realpt.y=%g", pt.x, pt.y);
		if (bullet->getBoundingBox().containsPoint(pt))
		{
			realpt = pt;
			CCLOG("TouchBegan:pt.x=%g,pt.y=%g", pt.x, pt.y);
			return true;//返回值决定消息是否要发到别的touch函数
		}
		return false;
	};

	mylistener->onTouchMoved = [=](Touch* touch, Event* event) mutable//指移动时
	{
		Vec2 pt = touch->getDelta();//这个函数获得的是前一个点和后一个点的差值
		realpt += pt;
		CCLOG("TouchMoved:pt.x=%g,pt.y=%g", pt.x, pt.y);
		if (0 <= realpt.x&&rect.getMaxX() >= realpt.x)
		{
			bullet->setPositionX(realpt.x);
		}
		if (0 <= realpt.y&&rect.getMaxY() >= realpt.y)
		{
			bullet->setPositionY(realpt.y);
		}
		if (realpt.x < 0)
		{
			bullet->setPositionX(0);
		}
		if (realpt.x > rect.getMaxX())
		{
			bullet->setPositionX(rect.getMaxX());
		}
		if (realpt.y < 0)
		{
			bullet->setPositionY(0);
		}
		if (realpt.y > rect.getMaxY())
		{
			bullet->setPositionY(rect.getMaxY());
		}
	};
	mylistener->onTouchEnded = [=](Touch* touch, Event* event) //松开时
	{
		CCLOG("TouchEnded");
	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(mylistener, this);

}