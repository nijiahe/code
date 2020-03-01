#include "enemy3.h"
#include "Bullet2.h"
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

bool enemy3::init()
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


void enemy3::init_with_picture()
{
	this->initWithSpriteFrameName("enemy3_n1.png");
}
void enemy3::play_plane_boom_animation()
{
	Animation * enemy3_boom_animation = AnimationCache::getInstance()->getAnimation("enemy3_boom_animation");
	Animate * enemy3_boom_animate = Animate::create(enemy3_boom_animation);
	this->runAction(enemy3_boom_animate);
}
void enemy3::play_plane_injured_action()
{
	Animation * enemy3_hit_animation = AnimationCache::getInstance()->getAnimation("enemy3_hit_animation");
	Animate * enemy3_hit_animate = Animate::create(enemy3_hit_animation);
	this->runAction(enemy3_hit_animate);
}
void enemy3::reset_plane()
{
	life_present = 5;
	life_max = 5;
}

void enemy3::enemy_fly_action()
{
	Size visible = Director::getInstance()->getWinSize();
	float move_far = CCRANDOM_0_1()*visible.width*0.6+visible.width*0.4;
	float fly_time = move_far / this->fly_speed;

	this->runAction(MoveTo::create(fly_time, Vec2(move_far,0)));
}
void enemy3::enemy_shoot_action(float t)
{
	MainGameLayer * mainlayer = dynamic_cast<MainGameLayer *>((dynamic_cast<Enemy_Plane_GameLayer*>(getParent()))->getParent());
	Size visible = Director::getInstance()->getWinSize();
	Bullet2 * bullet1 = Bullet2::create();
	bullet1->setAnchorPoint(Vec2(0.5, 1));
	bullet1->setPosition(getPositionX(), getPositionY());
	mainlayer->_Bullet_Enemy_GameLayer->add_bullet(bullet1);
	float bullet_time1 = visible.height / mainlayer->_Bullet_Enemy_GameLayer->bullet_speed;
	bullet1->runAction(RepeatForever::create(MoveBy::create(bullet_time1 ,Vec2(0,-visible.height))));

	Bullet2 * bullet2 = Bullet2::create();
	bullet2->setAnchorPoint(Vec2(0.5, 1));
	bullet2->setPosition(getPositionX(), getPositionY());
	mainlayer->_Bullet_Enemy_GameLayer->add_bullet(bullet2);
	float bullet_time2 = visible.height / mainlayer->_Bullet_Enemy_GameLayer->bullet_speed;
	bullet2->runAction(RepeatForever::create(MoveBy::create(bullet_time2, Vec2(visible.width, -visible.height))));

	Bullet2 * bullet3 = Bullet2::create();
	bullet3->setAnchorPoint(Vec2(0.5, 1));
	bullet3->setPosition(getPositionX(), getPositionY());
	mainlayer->_Bullet_Enemy_GameLayer->add_bullet(bullet3);
	float bullet_time3 = visible.height / mainlayer->_Bullet_Enemy_GameLayer->bullet_speed;
	bullet3->runAction(RepeatForever::create(MoveBy::create(bullet_time3, Vec2(-visible.width, -visible.height))));
}

void enemy3::run_enemy_shoot_aciont()
{
	schedule(SEL_SCHEDULE(&enemy3::enemy_shoot_action), 3);
}

void enemy3::init_fly_speed()
{
	Size visible = Director::getInstance()->getWinSize();
	fly_speed = visible.width  / 4;
}

void enemy3::died_action()
{
	SimpleAudioEngine::getInstance()->playEffect("sound/enemy3_down.wav");
	dynamic_cast<MainGameLayer *>(getParent()->getParent())->_Game_Control_layer->Update_Score(500);
	Animation * plane_boom_animation = AnimationCache::getInstance()->getAnimation("enemy3_boom_animation");
	Animate * plane_boom_animate = Animate::create(plane_boom_animation);
	CallFunc * callfunc = CallFunc::create(CC_CALLBACK_0(enemy::remove_callback, this));
	Sequence * sequence = Sequence::createWithTwoActions(plane_boom_animate, callfunc);
	this->runAction(sequence);
}