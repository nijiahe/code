#include "Start_Layer.h"
#include "Screen_Select_Layer.h"
#include "cocos-ext.h"//cocos2dx扩展头文件
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;//SimpleAudioEngine声音文件的命名空间

USING_NS_CC_EXT;


bool Start_Layer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	load_source();
	srand(time(NULL));
	Sprite * tittle = Sprite::create("start_source/ScenceStart.png");
	tittle->setPosition(Winsize.width*0.5,Winsize.height*0.7);
	tittle->setContentSize(Size(Winsize.width*0.6, Winsize.height*0.4));
	tittle->setAnchorPoint(Vec2(0.5, 0.5));
	addChild(tittle);

	Sprite * spr1 = Sprite::create("start_source/playgameNormal.png");
	spr1->setContentSize(Size(Winsize.width*0.2, Winsize.height*0.2 / 167 * 38));
	Sprite * spr2 = Sprite::create("start_source/playgameClose.png");
	spr2->setContentSize(Size(Winsize.width*0.2, Winsize.width*0.2 / 167 * 38));
	MenuItem * item = MenuItemSprite::create(spr1, spr2,CC_CALLBACK_1(Start_Layer::start_game_menu_callfunc,this) );
	Menu * menu = Menu::create(item,NULL);
	addChild(menu);

	
	return true;
}

void Start_Layer::start_game_menu_callfunc(Ref * ref)
{
	Director::getInstance()->replaceScene(Common::createscene(Screen_Select_Layer::create()));
}

void Start_Layer::load_source()
{
	// 预加载音效
	SimpleAudioEngine::getInstance()->preloadEffect("sounds/bonus.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sounds/brickhit.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sounds/eexplosion.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sounds/gameover.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sounds/ice.wav");

	SimpleAudioEngine::getInstance()->preloadEffect("sounds/levelstarting.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sounds/life.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sounds/moving.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sounds/nmoving.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sounds/pause.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sounds/shieldhit.wav");

	SimpleAudioEngine::getInstance()->preloadEffect("sounds/shoot.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sounds/steelhit.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sounds/tbonushit.wav");

}