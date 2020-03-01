#include "MainGameLayer.h"
#include "Plane_GameLayer.h"
#include "Bullet_GameLayer.h"
#include "Enemy_Plane_GameLayer.h"
#include "Bullet_Enemy_GameLayer.h"
#include "Game_Control_layer.h"
#include "Game_End_Layer.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

bool MainGameLayer::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}
	add_background();
	run_background();
	add_Plane_GameLayer();
	add_Bullet_GameLayer();
	add_Enemy_Plane_GameLayer();
	add_Bullet_Enemy_GameLayer();
	add_Game_Control_Layer();
	play_background_music();

	return true;
}
Scene * MainGameLayer::createscene()
{
	Scene * scene = Scene::create();
	MainGameLayer * layer = MainGameLayer::create();
	scene->addChild(layer);
	return scene;
}

void MainGameLayer::add_background()
{
	Size visible = Director::getInstance()->getWinSize();
	Sprite * background1 = Sprite::createWithSpriteFrameName("background.png");
	background1->setAnchorPoint(Vec2(0, 0));
	background1->setContentSize(Size(visible.width, visible.height));
	background1->setPosition(0, 0);
	background1->setTag(background1_sprite_tag);
	addChild(background1);

	Sprite * background2 = Sprite::createWithSpriteFrameName("background.png");
	background2->setAnchorPoint(Vec2(0, 0));
	background2->setContentSize(Size(visible.width, visible.height));
	background2->setPosition(0, background2->getContentSize().height);
	background2->setTag(background2_sprite_tag);
	addChild(background2);
}

void MainGameLayer::run_background()
{
	schedule(SEL_SCHEDULE(&MainGameLayer::background_run_callback));
}

void MainGameLayer::stop_run_background()
{
	unschedule(SEL_SCHEDULE(&MainGameLayer::background_run_callback));
}

void MainGameLayer::background_run_callback(float t)
{
	Sprite * background1 = dynamic_cast<Sprite *>(getChildByTag(background1_sprite_tag));
	Sprite * background2 = dynamic_cast<Sprite *>(getChildByTag(background2_sprite_tag));

	background1->setPositionY(background1->getPositionY() - 2);
	background2->setPositionY(background2->getPositionY() - 2);
	if (background1->getPositionY()+background1->getContentSize().height <= 0)
	{
		background1->setPositionY(background2->getPositionY() +background2->getContentSize().height - 2);
	}
	if (background2->getPositionY() + background2->getContentSize().height <= 0)
	{
		background2->setPositionY(background1->getPositionY() + background1->getContentSize().height - 2);
	}
}

void MainGameLayer::play_background_music()
{
	SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/game_music.wav");
}

void MainGameLayer::add_Plane_GameLayer()
{
	_Plane_Layer = Plane_GameLayer::create();
	_Plane_Layer->setPosition(0, 0);
	_Plane_Layer->setAnchorPoint(Vec2(0, 0));
	addChild(_Plane_Layer);
}

void MainGameLayer::add_Bullet_GameLayer()
{
	_Bullet_Layer = Bullet_GameLayer::create();
	_Bullet_Layer->setPosition(0, 0);
	_Bullet_Layer->setAnchorPoint(Vec2(0, 0));
	addChild(_Bullet_Layer);
}

void MainGameLayer::add_Enemy_Plane_GameLayer()
{
	_Enemy_Plane_GameLayer = Enemy_Plane_GameLayer::create();
	_Enemy_Plane_GameLayer->setPosition(0, 0);
	_Enemy_Plane_GameLayer->setAnchorPoint(Vec2(0, 0));
	addChild(_Enemy_Plane_GameLayer);
}

void MainGameLayer::add_Bullet_Enemy_GameLayer()
{
	_Bullet_Enemy_GameLayer = Bullet_Enemy_GameLayer::create();
	_Bullet_Enemy_GameLayer->setPosition(0, 0);
	_Bullet_Enemy_GameLayer->setAnchorPoint(Vec2(0, 0));
	addChild(_Bullet_Enemy_GameLayer);
}

void MainGameLayer::add_Game_Control_Layer()
{
	_Game_Control_layer = Game_Control_layer::create();
	_Game_Control_layer->setPosition(0, 0);
	_Game_Control_layer->setAnchorPoint(Vec2(0, 0));
	addChild(_Game_Control_layer);
}

void MainGameLayer::add_Game_End_Layer()
{
	_Game_End_Layer = Game_End_Layer::create();
	_Game_End_Layer->setPosition(0, 0);
	_Game_End_Layer->setAnchorPoint(Vec2(0, 0));
	addChild(_Game_End_Layer);

}