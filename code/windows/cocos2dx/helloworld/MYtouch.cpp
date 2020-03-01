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
	Sprite* bullet = dynamic_cast<Sprite*>(getChildByTag(BULLET));//���ุ��ת��

	EventListenerTouchOneByOne* mylistener = EventListenerTouchOneByOne::create();//����һ����������
	Rect rect = Rect(0, 0, visible.width, visible.height);//���ô�������
	mylistener->setSwallowTouches(true);//�����Ƿ����ɴ���
	Vec2 realpt = bullet->getPosition();
	mylistener->onTouchBegan = [=](Touch* touch, Event* event) mutable//ָ����ʱ
	{ //[]�м���Ǵ���Ĳ���  
	  /*eventֻ��ƻ��ϵͳ������*/
	  /*typedef Vec2 Point;*//*Vec2����Point*/
		Vec2 pt = touch->getLocation();
		CCLOG("TouchBegan:realpt.x=%g,realpt.y=%g", pt.x, pt.y);
		if (bullet->getBoundingBox().containsPoint(pt))
		{
			realpt = pt;
			CCLOG("TouchBegan:pt.x=%g,pt.y=%g", pt.x, pt.y);
			return true;//����ֵ������Ϣ�Ƿ�Ҫ�������touch����
		}
		return false;
	};

	mylistener->onTouchMoved = [=](Touch* touch, Event* event) mutable//ָ�ƶ�ʱ
	{
		Vec2 pt = touch->getDelta();//���������õ���ǰһ����ͺ�һ����Ĳ�ֵ
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
	mylistener->onTouchEnded = [=](Touch* touch, Event* event) //�ɿ�ʱ
	{
		CCLOG("TouchEnded");
	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(mylistener, this);

}