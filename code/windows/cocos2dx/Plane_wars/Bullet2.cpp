#include "Bullet2.h"
#include "MainGameLayer.h"
#include "Plane_GameLayer.h"
#include "plane.h"
#include "Bullet_Enemy_GameLayer.h"

bool Bullet2::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	this->initWithSpriteFrameName("bullet2.png");

	return true;
}

bool Bullet2::out_of_visible()
{
	Size visible = Director::getInstance()->getWinSize();
	if (getPositionX() + getBoundingBox().size.width * (1 - getAnchorPoint().x) >= visible.width)
	{
		return true;
	}
	else if (getPositionX() - getBoundingBox().size.width * getAnchorPoint().x <= 0)
	{
		return true;
	}
	else if (getPositionY() + getBoundingBox().size.height * (1 - getAnchorPoint().y) >= visible.height)
	{
		return true;
	}
	else if (getPositionY() - getBoundingBox().size.height * -getAnchorPoint().y <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Bullet2::is_hit_plane()
{
	MainGameLayer * mainlayer = dynamic_cast<MainGameLayer *>(dynamic_cast<Bullet_Enemy_GameLayer *>(getParent())->getParent());
	if (!mainlayer->_Plane_Layer->_plane->is_died())
	{
		if (this->getBoundingBox().intersectsRect(mainlayer->_Plane_Layer->_plane->getBoundingBox())&&
			!mainlayer->_Plane_Layer->_plane->is_invincible)
		{
			return true;
		}
	}
	return false;
}