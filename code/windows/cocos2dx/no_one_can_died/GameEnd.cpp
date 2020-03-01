#include "GameEnd.h"
#include "Game_back_layer.h"
#include "StartLayer.h"

bool GameEnd::init(int degree_of_difficulty)
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}
	Size visible = Director::getInstance()->getWinSize();
	this->degree_of_difficulty = degree_of_difficulty;

	MenuItem * again_item = MenuItemLabel::create(Label::createWithTTF("Play Again", "fonts/arial.ttf", 40),
		CC_CALLBACK_1(GameEnd::again_menu_callback, this));
	MenuItem * back_item = MenuItemLabel::create(Label::createWithTTF("Back To Menu", "fonts/arial.ttf", 40),
		CC_CALLBACK_1(GameEnd::back_menu_callback, this));
	again_item->setColor(Color3B(0, 0, 0));
	back_item->setColor(Color3B(0, 0, 0));
	Menu * menu = Menu::create(again_item, back_item, NULL);
	menu->alignItemsVerticallyWithPadding(0.25*visible.height);
	addChild(menu);

	return true;
}


Scene * GameEnd::createscene(int degree_of_difficulty)
{
	Scene * scene = Scene::create();
	GameEnd * layer = GameEnd::create(degree_of_difficulty);
	scene->addChild(layer);
	return scene;
}

GameEnd * GameEnd::create(int degree_of_difficulty)
{
	GameEnd * pRet = new GameEnd;
	if (pRet&&pRet->init(degree_of_difficulty))
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

void GameEnd::again_menu_callback(Ref * ref)
{
	Scene * scene = Game_back_layer::createscene(this->degree_of_difficulty);
	Director::getInstance()->replaceScene(scene);
}

void GameEnd::back_menu_callback(Ref * ref)
{
	Scene * scene = StartLayer::createscene();
	Director::getInstance()->replaceScene(scene);
}