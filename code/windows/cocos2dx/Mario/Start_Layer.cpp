#include "Start_Layer.h"
#include "Grounds_Select_Layer.h"

bool Start_Layer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	Sprite * spr = Sprite::create("BackGround/background.png");
	spr->setPosition(Winsize.width*0.5, Winsize.height*0.5);
	spr->setContentSize(Size(Winsize.width, Winsize.height));
	addChild(spr);
	MenuItem * start_item = MenuItemImage::create("Menu/startgame_normal.png", "Menu/startgame_select.png", CC_CALLBACK_1(Start_Layer::startgame_item_callback,this));
	MenuItem * seting_item = MenuItemImage::create("Menu/Setting_n.png", "Menu/setting_s.png", CC_CALLBACK_1(Start_Layer::seting_item_callback, this));
	MenuItem * quitgame_item = MenuItemImage::create("Menu/quitgame_normal.png", "Menu/quitgame_select.png", CC_CALLBACK_1(Start_Layer::quitgame_item_callback, this));
	MenuItem * about_item = MenuItemImage::create("Menu/about_normal.png", "Menu/about_select.png", CC_CALLBACK_1(Start_Layer::about_item_callback, this));
	/*start_item->setScale(1.5f);
	seting_item->setScale(1.5f);
	quitgame_item->setScale(1.5f);
	about_item->setScale(1.3f);*/
	Menu * menu = Menu::create(start_item, seting_item, quitgame_item, about_item, NULL);
	addChild(menu);
	menu->setPositionY(Winsize.height*0.27);
	menu->alignItemsVerticallyWithPadding(Winsize.height*0.04);
	Common::MoveNode(about_item, Vec2(Winsize.width*0.4, 0));
	return true;
}

void Start_Layer::startgame_item_callback(Ref * ref)
{
	Grounds_Select_Layer * layer = Grounds_Select_Layer::create();
	Scene * scene = Common::createscene(layer);
	Director::getInstance()->replaceScene(scene);
}

void Start_Layer::seting_item_callback(Ref * ref)
{

}

void Start_Layer::quitgame_item_callback(Ref * ref)
{
	Director::getInstance()->end();
}

void Start_Layer::about_item_callback(Ref * ref)
{

}