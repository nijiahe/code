#include "enemy1.h"
#include "math.h"
#include "MainGameLayer.h"
#include "Enemy_Plane_GameLayer.h"
#include "Bullet2.h"
#include "enemy.h"
#include "Plane_GameLayer.h"
#include "plane.h"
#include "Bullet_Enemy_GameLayer.h"
#include "Game_Control_layer.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

bool enemy1::init()
{
	if (!enemy::init())
	{
		return false;
	}
	init_fly_speed();
	init_with_picture();
	reset_plane();
	enemy_fly_action();
	run_enemy_shoot_aciont();
	return true;
}


void enemy1::init_with_picture()
{
	this->initWithSpriteFrameName("enemy1.png");
}
void enemy1::play_plane_boom_animation()
{
	Animation * enemy1_boom_animation = AnimationCache::getInstance()->getAnimation("enemy1_boom_animation");
	Animate * enemy1_boom_animate = Animate::create(enemy1_boom_animation);
	this->runAction(enemy1_boom_animate);
}
void enemy1::play_plane_injured_action()
{
	
}
void enemy1::reset_plane()
{
	life_present = 1;
	life_max = 1;
}

void enemy1::enemy_fly_action()
{
	Size visible = Director::getInstance()->getWinSize();
	this->runAction(MoveBy::create(visible.height*1.5/fly_speed, Vec2(0, -visible.height*1.5)));
}

void enemy1::enemy_shoot_action(float t)
{
	MainGameLayer * mainlayer = dynamic_cast<MainGameLayer *>((dynamic_cast<Enemy_Plane_GameLayer*>(getParent()))->getParent());
	if (!mainlayer->_Plane_Layer->_plane->is_died())
	{
		Vec2 plane_position = mainlayer->_Plane_Layer->_plane->getPosition();
		Bullet2 * bullet = Bullet2::create();
		bullet->setAnchorPoint(Vec2(0.5, 1));
		bullet->setPosition(getPositionX(), getPositionY());
		mainlayer->_Bullet_Enemy_GameLayer->add_bullet(bullet);
		float num = (getPositionX() - plane_position.x) *(getPositionX() - plane_position.x) +
			(getPositionY() - plane_position.y) *(getPositionY() - plane_position.y);
		float bullet_time = sqrt(num) / mainlayer->_Bullet_Enemy_GameLayer->bullet_speed;
		bullet->runAction(RepeatForever::create(MoveBy::create(bullet_time, plane_position - this->getPosition())));
	}
	
}

void enemy1::run_enemy_shoot_aciont()
{
	schedule(SEL_SCHEDULE(&enemy1::enemy_shoot_action),2);
}

void enemy1::init_fly_speed()
{
	Size visible = Director::getInstance()->getWinSize();
	fly_speed = visible.width*1.5 / 10;
}

void enemy1::died_action()
{
	SimpleAudioEngine::getInstance()->playEffect("sound/enemy1_down.wav");
	dynamic_cast<MainGameLayer *>(getParent()->getParent())->_Game_Control_layer->Update_Score(100);
	Animation * plane_boom_animation = AnimationCache::getInstance()->getAnimation("enemy1_boom_animation");
	Animate * plane_boom_animate = Animate::create(plane_boom_animation);
	CallFunc * callfunc = CallFunc::create(CC_CALLBACK_0(enemy::remove_callback, this));
	Sequence * sequence = Sequence::createWithTwoActions(plane_boom_animate, callfunc);
	this->runAction(sequence);
}