#include "lostlayer.h"
#include "diffeculty_select.h"
#include "GameStartLayer.h"
#include "background.h"
#include "gamelayer.h"
#include "cocos-ext.h"//cocos2dx扩展头文件
#include "SimpleAudioEngine.h"
USING_NS_CC_EXT;
using namespace CocosDenshion;

bool lostlayer::init()
{
	if (!LayerColor::initWithColor(Color4B(105, 105, 105, 180)))
	{
		return false;
	}
	Size visible = Director::getInstance()->getWinSize();

	/*设置YOU LOST标题*/

	Label* title1 = Label::createWithBMFont("fonts/bitmapFontTest3.fnt", "YOU LOST");
	title1->setPosition(visible.width*0.5, visible.height*0.7);
	title1->setTag(bmfonttag);
	title1->setScale(3);
	addChild(title1);


	/*设置 TRY AGAIN menu*/
	Label* tyragain_label = Label::createWithTTF("TRY AGAIN", "fonts/Marker Felt.ttf", 35);
	//startlabel->setAnchorPoint(Vec2(0, 0));
	tyragain_label->enableOutline(Color4B(0, 0, 255, 255), 15);
	tyragain_label->enableGlow(Color4B(0, 0, 0, 255));
	tyragain_label->setTag(tyragain_labeltag);
	MenuItem* tyragain_menu = MenuItemLabel::create(tyragain_label, CC_CALLBACK_1(lostlayer::tryagainfunc, this));
	tyragain_menu->setTag(tyragain_menutag);
	tyragain_menu->setScale(0.6f);
	tyragain_menu->setColor(Color3B(0, 0, 0));

	/*设置back to menu func*/
	Label* backtomenu_label = Label::createWithTTF("BACK TO MENU", "fonts/Marker Felt.ttf", 35);
	//startlabel->setAnchorPoint(Vec2(0, 0));
	backtomenu_label->enableOutline(Color4B(0, 0, 255, 255), 15);
	backtomenu_label->enableGlow(Color4B(0, 0, 0, 255));
	backtomenu_label->setTag(backtomenu_labeltag);
	MenuItem* backtomenu_menu = MenuItemLabel::create(backtomenu_label, CC_CALLBACK_1(lostlayer::backtomenufunc, this));
	backtomenu_menu->setTag(backtomenu_menutag);
	backtomenu_menu->setScale(0.6f);
	backtomenu_menu->setColor(Color3B(0, 0, 0));

	Menu* menu = Menu::create(tyragain_menu, backtomenu_menu, NULL);
	menu->alignItemsVerticallyWithPadding(visible.height*0.2);
	tyragain_menu->setPositionY(0);
	backtomenu_menu->setPositionY(backtomenu_menu->getPositionY() - 0.1*visible.height);
	addChild(menu);

	return true;
}

Scene* lostlayer::createscene()
{
	Scene* scene = Scene::create();
	lostlayer* layer = lostlayer::create();
	scene->addChild(layer);
	return scene;
}

void lostlayer::tryagainfunc(Ref* ref)
{
	SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
	diffeculty_select* layer = diffeculty_select::create();
	dynamic_cast<Scene*>(dynamic_cast<gamelayer*>(this->getParent())->getParent())->addChild(layer);
	dynamic_cast<gamelayer*>(this->getParent())->removeFromParent();
}
void lostlayer::backtomenufunc(Ref* ref)
{
	SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
	GameStartLayer* layer = GameStartLayer::create();
	dynamic_cast<Scene*>(dynamic_cast<gamelayer*>(this->getParent())->getParent())->addChild(layer);
	dynamic_cast<gamelayer*>(this->getParent())->removeFromParent();
}