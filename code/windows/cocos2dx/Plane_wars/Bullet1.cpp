#include "Bullet1.h"


bool Bullet1::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	this->initWithSpriteFrameName("bullet1.png");

	return true;
}

bool Bullet1::out_of_visible()
{
	Size visible = Director::getInstance()->getWinSize();
	if (getPositionX() + getBoundingBox().size.width * (1 - getAnchorPoint().x) >= visible.width)
	{
		return true;
	}
	else if(getPositionX() - getBoundingBox().size.width * getAnchorPoint().x <= 0)
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
bool Bullet1::is_hit_enemy()
{
	return false;
}