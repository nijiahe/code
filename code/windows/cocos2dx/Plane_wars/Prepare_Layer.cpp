#include "Prepare_Layer.h"

#include "MainGameLayer.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

bool Prepare_Layer::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}
	load_resourse();
	set_background();
	play_action();

	return true;
}
Scene * Prepare_Layer::createscene()
{
	Scene * scene = Scene::create();
	Prepare_Layer * layer = Prepare_Layer::create();
	scene->addChild(layer);
	return scene;
}

void Prepare_Layer::load_resourse()
{
	/*加载音乐资源*/
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound / game_music.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/achievement.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/big_spaceship_flying.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/bullet.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/button.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/enemy1_down.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/enemy2_down.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/enemy3_down.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/game_over.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/get_bomb.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/get_double_laser.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/out_porp.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/use_bomb.wav");

	/*加载图片资源*/
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui/shoot.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui/shoot_background.plist");
}
void Prepare_Layer::toMainGameLayer()
{
	Scene * scene = MainGameLayer::createscene();
	Director::getInstance()->replaceScene(scene);
}
void Prepare_Layer::play_action()
{
	Size visible = Director::getInstance()->getWinSize();
	Sprite * loading = Sprite::createWithSpriteFrameName("game_loading1.png");
	loading->setScale(2);
	loading->setPosition(visible.width *0.5, visible.height *0.5);
	
	addChild(loading);
	Animation * animation = Animation::create();
	animation->setDelayPerUnit(0.2f);
	animation->setLoops(4);
	for (int i = 1; i <= 4; i++)
	{
		__String* str = __String::createWithFormat("game_loading%d.png", i);
		SpriteFrame * frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str->getCString());
		animation->addSpriteFrame(frame);
	}
	Animate * animate = Animate::create(animation);
	CallFunc * callfunc = CallFunc::create(CC_CALLBACK_0(Prepare_Layer::toMainGameLayer, this));
	Sequence * sequence = Sequence::createWithTwoActions(animate, callfunc);
	loading->runAction(sequence);

}

void Prepare_Layer::set_background()
{
	Size visible = Director::getInstance()->getWinSize();
	Sprite * background = Sprite::createWithSpriteFrameName("background.png");
	background->setContentSize(Size(visible.width, visible.height));
	background->setAnchorPoint(Vec2(0, 0));
	background->setPosition(Vec2(0, 0));
	addChild(background);

	Sprite *copyright = Sprite::createWithSpriteFrameName("shoot_copyright.png");
	copyright->setAnchorPoint(Vec2(0.5, 0.5));
	copyright->setPosition(visible.width *0.5, visible.height *0.7);
	addChild(copyright);
}