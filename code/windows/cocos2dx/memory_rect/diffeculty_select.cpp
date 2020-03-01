#include "diffeculty_select.h"
#include "GameStartLayer.h"
#include "gamelayer.h"
#include "cocos-ext.h"//cocos2dx扩展头文件
#include "SimpleAudioEngine.h"
USING_NS_CC_EXT;
using namespace CocosDenshion;

bool diffeculty_select::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 0)))
	{
		return false;
	}
	

	Size visible = Director::getInstance()->getWinSize();

	/*EASY菜单*/
	Label* startlabel = Label::createWithTTF("EASY", "fonts/Marker Felt.ttf", 35);
	startlabel->enableOutline(Color4B(0, 0, 255, 255), 15);
	startlabel->enableGlow(Color4B(0, 0, 0, 255));
	startlabel->setTag(startlabeltag);
	MenuItem* startmenu = MenuItemLabel::create(startlabel, CC_CALLBACK_1(diffeculty_select::easyfunc, this));
	startmenu->setTag(startmenutag);
	startmenu->setScale(0.6f);
	startmenu->setColor(Color3B(0, 0, 0));

	/*HARD菜单*/
	Label* quitlabel = Label::createWithTTF("HARD", "fonts/Marker Felt.ttf", 35);
	quitlabel->enableOutline(Color4B(0, 0, 255, 255), 15);
	quitlabel->enableGlow(Color4B(0, 0, 0, 255));
	quitlabel->setTag(quitlabeltag);
	MenuItem* quitmenu = MenuItemLabel::create(quitlabel, CC_CALLBACK_1(diffeculty_select::hardfunc, this));
	quitmenu->setTag(quitmenutag);
	quitmenu->setScale(0.6f);
	quitmenu->setColor(Color3B(0, 0, 0));

	/*back菜单*/
	Label* backlabel = Label::createWithTTF("BACK", "fonts/Marker Felt.ttf", 35);
	backlabel->enableOutline(Color4B(0, 0, 255, 255), 15);
	backlabel->enableGlow(Color4B(0, 0, 0, 255));
	backlabel->setTag(backlabeltag);
	MenuItem* backmenu = MenuItemLabel::create(backlabel, CC_CALLBACK_1(diffeculty_select::backfunc, this));
	backmenu->setTag(backmenutag);
	backmenu->setScale(0.6f);
	backmenu->setColor(Color3B(0, 0, 0));


	/*设置菜单位置*/
	Menu* menu = Menu::create(startmenu, quitmenu, backmenu, NULL);
	menu->alignItemsVerticallyWithPadding(visible.height*0.2);
	startmenu->setPositionY(startmenu->getPositionY() - 0.1*visible.height);
	quitmenu->setPositionY(quitmenu->getPositionY() - 0.1*visible.height);
	backmenu->setPositionY(backmenu->getPositionY() - 0.1*visible.height);
	addChild(menu);
	return true;
}

Scene* diffeculty_select::createscene()
{
	Scene* scene = Scene::create();
	diffeculty_select* layer = diffeculty_select::create();
	scene->addChild(layer);
	return scene;
}

void diffeculty_select::easyfunc(Ref* ref)
{
	SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
	gamelayer* layer = gamelayer::create(5);
	dynamic_cast<Scene*>(this->getParent())->addChild(layer);
	this->removeFromParent();
}
void diffeculty_select::hardfunc(Ref* ref)
{
	SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
	gamelayer* layer = gamelayer::create(7);
	dynamic_cast<Scene*>(this->getParent())->addChild(layer);
	this->removeFromParent();
}

void diffeculty_select::backfunc(Ref* ref)
{
	SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
	GameStartLayer* layer = GameStartLayer::create();
	dynamic_cast<Scene*>(this->getParent())->addChild(layer);
	this->removeFromParent();
}