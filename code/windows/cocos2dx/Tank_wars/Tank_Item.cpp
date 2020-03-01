#include "Tank_Item.h"
#include "Game_Layer.h"

bool Tank_Item::init(Common::Item_Type type)
{
	if (!Sprite::init())
	{
		return false;
	}

	_type = type;
	if (type == Common::Item_Type::active)
	{
		set_picture("item/active.png");
	}
	else if (type == Common::Item_Type::bomb)
	{
		set_picture("item/bomb.png");
	}
	else if (type == Common::Item_Type::mintank)
	{
		set_picture("item/mintank.png");
	}
	else if (type == Common::Item_Type::star)
	{
		set_picture("item/star.png");
	}
	else if (type == Common::Item_Type::steel)
	{
		set_picture("item/steel.png");
	}
	else if (type == Common::Item_Type::timer)
	{
		set_picture("item/timer.png");
	}

	return true;
}
Tank_Item * Tank_Item::create(Common::Item_Type type)
{
	Tank_Item * pRet = new Tank_Item;
	if (pRet&&pRet->init(type))
	{
		pRet->autorelease();
	}
	else
	{
		delete pRet;
		pRet = NULL;
	}
	return pRet;
}


void Tank_Item::set_picture(const char* filename)
{
	Texture2D* texture = Director::getInstance()->getTextureCache()->addImage(filename);

	setTexture(texture);
	setTextureRect(Rect(0, 0, texture->getContentSize().width, texture->getContentSize().height));
	
}