#include "background.h"
#include "cocos-ext.h"//cocos2dx扩展头文件
#include "SimpleAudioEngine.h"
USING_NS_CC_EXT;
using namespace CocosDenshion;


bool background::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}
	
	SimpleAudioEngine::getInstance()->preloadEffect("sound/button.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/achievement.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/game_over.wav");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/game_music.wav");
	SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/game_music.wav");

	Size visible = Director::getInstance()->getWinSize();

	Sprite* background = Sprite::create("background.jpg");
	background->setContentSize(Size(visible.width, visible.height));
	background->setTag(backgroundspritetag);
	background->setPosition(visible.width*0.5, visible.height*0.5);
	addChild(background);

	/*标题Label*/
	Label* title1 = Label::createWithBMFont("fonts/bitmapFontTest3.fnt", "MEMORY");
	title1->setPosition(visible.width*0.45, visible.height*0.9);
	title1->setTag(title1tag);
	title1->setScale(4);
	addChild(title1);

	/*标题Label*/
	Label* title2 = Label::createWithBMFont("fonts/bitmapFontTest3.fnt", "RECT");
	title2->setPosition(visible.width*0.6, visible.height*0.8);
	title2->setTag(title2tag);
	title2->setScale(3);
	addChild(title2);


	return true;
}

Scene* background::createscene()
{
	Scene* scene = Scene::create();
	background* layer = background::create();
	scene->addChild(layer);
	return scene;
}

