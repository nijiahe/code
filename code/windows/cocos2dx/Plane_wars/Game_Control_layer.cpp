#include "Game_Control_layer.h"
#include "MainGameLayer.h"
#include "Plane_GameLayer.h"
#include "plane.h"


bool Game_Control_layer::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 0)))
	{
		return false;
	}
	add_Pause_Menu();
	add_Score_Label();
	add_Plane_life_visible();
	add_Bomb_Menu();
	add_Bomb_Count_visible();

	return true;
}


void Game_Control_layer::add_Pause_Menu()
{
	Size visible = Director::getInstance()->getWinSize();
	MenuItem * pause_item = MenuItemSprite::create(Sprite::createWithSpriteFrameName("game_pause_nor.png"), Sprite::createWithSpriteFrameName("game_pause_pressed.png"));
	MenuItem * continue_item = MenuItemSprite::create(Sprite::createWithSpriteFrameName("game_resume_nor.png"), Sprite::createWithSpriteFrameName("game_resume_pressed.png"));
	pause_item->setTag(pause_item_tag);
	continue_item->setTag(continue_item_tag);
	Pause_Menu_Toogle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(Game_Control_layer::Pause_And_Continue_Menu_callback, this), pause_item, continue_item,NULL);
	Pause_Menu_Toogle->setAnchorPoint(Vec2(0, 1));
	Pause_Menu_Toogle->setPosition(0, visible.height*0.97);
	Menu *Pause_Menu = Menu::create(Pause_Menu_Toogle, NULL);
	Pause_Menu->setPosition(Vec2(0, 0));
	Pause_Menu->setAnchorPoint(Vec2(0, 0));
	addChild(Pause_Menu);
}
void Game_Control_layer::add_Score_Label()
{
	Score_Lalel = Label::createWithBMFont("fonts/font.fnt", "000000");
	Score_Lalel->setScale(1.7f);
	Score_Lalel->setColor(Color3B(143, 146, 147));
	Score_Lalel->setAnchorPoint(Vec2(0, 1));
	Score_Lalel->setPosition(Vec2(Pause_Menu_Toogle->getPositionX()+ Pause_Menu_Toogle->getBoundingBox().size.width, Pause_Menu_Toogle->getPositionY()));
	addChild(Score_Lalel);
}

void Game_Control_layer::add_Plane_life_visible()
{
	Size visible = Director::getInstance()->getWinSize();
	Sprite * picture = Sprite::createWithSpriteFrameName("hero1.png");
	picture->setScale(0.5);
	picture->setAnchorPoint(Vec2(0.5, 0.5));
	picture->setPosition(visible.width*0.7, visible.height*0.15);
	addChild(picture);

	Plane_Life = Label::createWithBMFont("fonts/font.fnt", "3");
	Plane_Life->setScale(1.3f);
	Plane_Life->setColor(Color3B(143, 146, 147));
	Plane_Life->setAnchorPoint(Vec2(0.5,0.5));
	Plane_Life->setPosition(Vec2(picture->getPositionX() + picture->getBoundingBox().size.width*2, picture->getPositionY()));
	addChild(Plane_Life);
}
void Game_Control_layer::Update_Plane_life_visible()
{
	__String* str = __String::createWithFormat("%d", dynamic_cast<MainGameLayer *>(getParent())->_Plane_Layer->_plane->life_present);
	Plane_Life->setString(str->getCString());
}
void Game_Control_layer::add_Bomb_Menu()
{

}
void Game_Control_layer::add_Bomb_Count_visible()
{

}
void Game_Control_layer::Update_Bomb_Count_visible()
{

}
void Game_Control_layer::use_Bomb()
{

}
void Game_Control_layer::Bomb_Menu_callback()
{

}
void Game_Control_layer::Pause_And_Continue_Menu_callback(Ref * ref)
{
	MenuItemToggle* item = dynamic_cast<MenuItemToggle*>(ref);
	switch (item->getSelectedIndex())
	{
	case pause_item_tag:
		Director::getInstance()->resume();
		dynamic_cast<MainGameLayer *>(getParent())->_Plane_Layer->runtouch();
		break;
	case continue_item_tag:
		Director::getInstance()->pause();
		dynamic_cast<MainGameLayer *>(getParent())->_Plane_Layer->closetouch();
		break;
	}
}

void Game_Control_layer::Update_Score(int num)
{
	score += num;
	__String* str = __String::createWithFormat("%d", score);
	Score_Lalel->setString(str->getCString());
}