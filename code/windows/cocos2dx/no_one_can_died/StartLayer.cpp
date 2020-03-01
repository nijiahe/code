#include "StartLayer.h"
#include "Game_back_layer.h"

bool StartLayer::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}
	srand(time(NULL));
	Size visible = Director::getInstance()->getWinSize();
	MenuItem * normal_item = MenuItemLabel::create(Label::createWithTTF("NORMAL", "fonts/arial.ttf", 30),
		CC_CALLBACK_1(StartLayer::normal_menu_callfunc,this));
	MenuItem * hard_item = MenuItemLabel::create(Label::createWithTTF("HARD", "fonts/arial.ttf", 30), 
		CC_CALLBACK_1(StartLayer::hard_menu_callfunc, this));
	MenuItem * hell_item = MenuItemLabel::create(Label::createWithTTF("HELL", "fonts/arial.ttf", 30), 
		CC_CALLBACK_1(StartLayer::hell_menu_callfunc, this));
	MenuItem * quit_item = MenuItemLabel::create(Label::createWithTTF("QUIT", "fonts/arial.ttf", 30), 
		CC_CALLBACK_1(StartLayer::quit_menu_callfunc, this));
	normal_item->setColor(Color3B(0, 0, 0));
	hard_item->setColor(Color3B(0, 0, 0));
	hell_item->setColor(Color3B(0, 0, 0));
	quit_item->setColor(Color3B(0, 0, 0));
	Menu * menu = Menu::create(normal_item, hard_item, hell_item, quit_item, NULL);
	menu->alignItemsVerticallyWithPadding(visible.height*0.15);
	addChild(menu);


	return true;
}


Scene * StartLayer::createscene()
{
	Scene * scene = Scene::create();
	StartLayer * layer = StartLayer::create();
	scene->addChild(layer);
	return scene;
}


void StartLayer::normal_menu_callfunc(Ref * ref)
{
	Scene * scene = Game_back_layer::createscene(normal);
	Director::getInstance()->replaceScene(scene);
}

void StartLayer::hard_menu_callfunc(Ref * ref)
{
	Scene * scene = Game_back_layer::createscene(hard);
	Director::getInstance()->replaceScene(scene);
}

void StartLayer::hell_menu_callfunc(Ref * ref)
{
	Scene * scene = Game_back_layer::createscene(hell);
	Director::getInstance()->replaceScene(scene);
}

void StartLayer::quit_menu_callfunc(Ref * ref)
{
	Director::getInstance()->end();
}