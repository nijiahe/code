#include "Plane_GameLayer.h"
#include "plane.h"


bool Plane_GameLayer::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 0)))
	{
		return false;
	}
	prepare_plane_animation();
	_plane = plane::create();
	addChild(_plane);
	runtouch();
	srand(time(NULL));
	

	return true;
}

void Plane_GameLayer::prepare_plane_animation()
{
	/*飞机飞行动画*/
	Animation * plane_fly_animation = Animation::create();
	plane_fly_animation->setDelayPerUnit(0.2f);
	plane_fly_animation->setLoops(-1);
	plane_fly_animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero1.png"));
	plane_fly_animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero2.png"));
	AnimationCache::getInstance()->addAnimation(plane_fly_animation, "plane_fly_animation");

	/*飞机爆炸动画*/
	Animation * plane_boom_animation = Animation::create();
	plane_boom_animation->setDelayPerUnit(0.2f);
	plane_boom_animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_blowup_n1.png"));
	plane_boom_animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_blowup_n2.png"));
	plane_boom_animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_blowup_n3.png"));
	AnimationCache::getInstance()->addAnimation(plane_boom_animation, "plane_boom_animation");

}

void Plane_GameLayer::runtouch()
{
	Size visible = Director::getInstance()->getWinSize();

	mylistener = EventListenerTouchOneByOne::create();//创建一个触摸监听
	mylistener->setSwallowTouches(false);//设置是否吞噬触摸
	mylistener->onTouchBegan = [=](Touch* touch, Event* event) mutable
	{ 
		Vec2 point = touch->getLocation();
		if (_plane->is_died())
		{
			return false;
		}
		if (_plane->getBoundingBox().containsPoint(point))
		{
			return true;
		}
		
	};
	mylistener->onTouchMoved = [=](Touch* touch, Event* event) mutable//指移动时
	{
		Vec2 point = touch->getDelta();
		if (!_plane->is_died())
		{
			if (point.x > 0)
			{
				if (_plane->getPositionX() + (1 - _plane->getAnchorPoint().x) * _plane->getBoundingBox().size.width <= visible.width)
				{
					_plane->setPositionX(_plane->getPositionX() + point.x);
				}
			}
			else
			{
				if (_plane->getPositionX() - _plane->getAnchorPoint().x * _plane->getBoundingBox().size.width >= 0)
				{
					_plane->setPositionX(_plane->getPositionX() + point.x);
				}
			}
			if (point.y > 0)
			{
				if (_plane->getPositionY() + (1 - _plane->getAnchorPoint().y) * _plane->getBoundingBox().size.height <= visible.height)
				{
					_plane->setPositionY(_plane->getPositionY() + point.y);
				}
			}
			else
			{
				if (_plane->getPositionY() - _plane->getAnchorPoint().y * _plane->getBoundingBox().size.height >= 0)
				{
					_plane->setPositionY(_plane->getPositionY() + point.y);
				}
			}
		}
	};
	mylistener->onTouchEnded = [=](Touch* touch, Event* event) //松开时
	{

	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(mylistener, this);
}

void Plane_GameLayer::closetouch()
{
	mylistener->onTouchBegan = [=](Touch* touch, Event* event) mutable
	{
		return false;
	};
}