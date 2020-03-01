#include "Bullet_Enemy.h"


bool Bullet_Enemy::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	return true;
}


void Bullet_Enemy::set_picture(const char * filename)
{
	Texture2D* texture = Director::getInstance()->getTextureCache()->addImage(filename);

	setTexture(texture);
	setTextureRect(Rect(0, 0, texture->getContentSize().width, texture->getContentSize().height));
}