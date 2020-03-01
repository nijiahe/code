#include "Bullet_Friend.h"

bool Bullet_Friend::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	return true;
}


void Bullet_Friend::set_picture(const char * filename)
{
	Texture2D* texture = Director::getInstance()->getTextureCache()->addImage(filename);

	setTexture(texture);
	setTextureRect(Rect(0, 0, texture->getContentSize().width,texture->getContentSize().height));
}