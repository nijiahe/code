#include "GameStartLayer.h"
#include "diffeculty_select.h"
#include "cocos-ext.h"//cocos2dx扩展头文件
#include "SimpleAudioEngine.h"
USING_NS_CC_EXT;
using namespace CocosDenshion;

bool GameStartLayer::init()
{
	if (!LayerColor::initWithColor(Color4B(255,255,255,0)))
	{
		return false;
	}
	Size visible = Director::getInstance()->getWinSize();

	/*statgame菜单*/
	Label* startlabel = Label::createWithTTF("START GAME", "fonts/Marker Felt.ttf", 35);
	//startlabel->setAnchorPoint(Vec2(0, 0));
	startlabel->enableOutline(Color4B(0, 0, 255, 255), 15);
	startlabel->enableGlow(Color4B(0, 0, 0, 255));
	startlabel->setTag(startlabeltag);
	MenuItem* startmenu = MenuItemLabel::create(startlabel, CC_CALLBACK_1(GameStartLayer::startfunc, this));
	startmenu->setTag(startmenutag);
	startmenu->setScale(0.6f);
	startmenu->setColor(Color3B(0, 0, 0));

	/*quit菜单*/
	Label* quitlabel = Label::createWithTTF("Quit", "fonts/Marker Felt.ttf", 35);
	quitlabel->enableOutline(Color4B(0, 0, 255, 255), 15);
	quitlabel->enableGlow(Color4B(0, 0, 0, 255));
	quitlabel->setTag(quitlabeltag);
	MenuItem* quitmenu = MenuItemLabel::create(quitlabel, CC_CALLBACK_1(GameStartLayer::quitfunc, this));
	quitmenu->setTag(quitmenutag);
	quitmenu->setScale(0.6f);
	quitmenu->setColor(Color3B(0, 0, 0));

	/*设置菜单位置*/
	Menu* menu = Menu::create(startmenu, quitmenu,NULL);
	menu->alignItemsVerticallyWithPadding(visible.height*0.2);
	startmenu->setPositionY(0);
	quitmenu->setPositionY(quitmenu->getPositionY() - 0.1*visible.height);
	addChild(menu);
	return true;
}

Scene* GameStartLayer::createscene()
{
	Size visible = Director::getInstance()->getWinSize();
	Scene* scene = Scene::create();
	GameStartLayer* layer = GameStartLayer::create();
	layer->setPosition(visible.width / 2, visible.height*0.4);
	scene->addChild(layer);
	return scene;
}

void GameStartLayer::startfunc(Ref* ref)
{
	SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
	diffeculty_select* diffeculty_select_layer = diffeculty_select::create();
	dynamic_cast<Scene*>(this->getParent())->addChild(diffeculty_select_layer);
	this->removeFromParent();
}
void GameStartLayer::quitfunc(Ref* ref)
{
	SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
	exit(0);
}