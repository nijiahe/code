#include "Enemy_Plane_GameLayer.h"
#include "MainGameLayer.h"
#include "Plane_GameLayer.h"
#include "plane.h"
#include "enemy1.h"
#include "enemy2.h"
#include "enemy3.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

bool Enemy_Plane_GameLayer::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 0)))
	{
		return false;
	}
	prepare_enemy_plane_animation();
	auto_add_enemy1(2);
	auto_add_enemy2(5);
	auto_add_enemy3(7);
	run_enemy_monitor();

	return true;
}

void Enemy_Plane_GameLayer::add_enemy1(float t)
{
	Size visible = Director::getInstance()->getWinSize();
	enemy1 * plane = enemy1::create(); 
	plane->setPosition(visible.width*CCRANDOM_0_1(), visible.height*1.0);
	plane->setAnchorPoint(Vec2(0.5, 0));
	addChild(plane); 
	enemy_vector.pushBack(plane);
}
void Enemy_Plane_GameLayer::add_enemy2(float t)
{
	Size visible = Director::getInstance()->getWinSize();
	enemy2 * plane = enemy2::create();
	plane->setPosition(visible.width*CCRANDOM_0_1(), visible.height*1.0);
	addChild(plane);
	enemy_vector.pushBack(plane);
}
void Enemy_Plane_GameLayer::add_enemy3(float t)
{
	SimpleAudioEngine::getInstance()->playEffect("sound/big_spaceship_flying.wav");
	Size visible = Director::getInstance()->getWinSize();
	enemy3 * plane = enemy3::create();
	float num = CCRANDOM_0_1();
	plane->setPosition(-plane->getBoundingBox().size.width*0.5 - visible.width*num*0.1, CCRANDOM_0_1()* visible.height*0.5+visible.height*0.5);
	addChild(plane);
	enemy_vector.pushBack(plane);
}

void Enemy_Plane_GameLayer::prepare_enemy_plane_animation()
{
	/*enemy1±¬Õ¨¶¯»­*/
	Animation * enemy1_boom_animation = Animation::create();
	enemy1_boom_animation->setDelayPerUnit(0.2f);
	enemy1_boom_animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down1.png"));
	enemy1_boom_animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down2.png"));
	enemy1_boom_animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down3.png"));
	enemy1_boom_animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down4.png"));
	AnimationCache::getInstance()->addAnimation(enemy1_boom_animation, "enemy1_boom_animation");

	/*enemy2±¬Õ¨¶¯»­*/
	Animation * enemy2_boom_animation = Animation::create();
	enemy2_boom_animation->setDelayPerUnit(0.2f);
	enemy2_boom_animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_down1.png"));
	enemy2_boom_animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_down2.png"));
	enemy2_boom_animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_down3.png"));
	enemy2_boom_animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_down4.png"));
	AnimationCache::getInstance()->addAnimation(enemy2_boom_animation, "enemy2_boom_animation");

	/*enemy3±¬Õ¨¶¯»­*/
	Animation * enemy3_boom_animation = Animation::create();
	enemy3_boom_animation->setDelayPerUnit(0.2f);
	enemy3_boom_animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down1.png"));
	enemy3_boom_animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down2.png"));
	enemy3_boom_animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down3.png"));
	enemy3_boom_animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down4.png"));
	enemy3_boom_animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down5.png"));
	enemy3_boom_animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down6.png"));
	AnimationCache::getInstance()->addAnimation(enemy3_boom_animation, "enemy3_boom_animation");


	/*enemy2»÷ÖÐ¶¯»­*/
	Animation * enemy2_hit_animation = Animation::create();
	enemy2_hit_animation->setDelayPerUnit(0.2f);
	enemy2_hit_animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_hit.png"));
	enemy2_hit_animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2.png"));
	AnimationCache::getInstance()->addAnimation(enemy2_hit_animation, "enemy2_hit_animation");

	/*enemy3»÷ÖÐ¶¯»­*/
	Animation * enemy3_hit_animation = Animation::create();
	enemy3_hit_animation->setDelayPerUnit(0.2f);
	enemy3_hit_animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_hit.png"));
	enemy3_hit_animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_n2.png"));
	AnimationCache::getInstance()->addAnimation(enemy3_hit_animation, "enemy3_hit_animation");
}

void Enemy_Plane_GameLayer::run_enemy_monitor()
{
	schedule(SEL_SCHEDULE(&Enemy_Plane_GameLayer::enemy_monitor_callback));
}

void Enemy_Plane_GameLayer::enemy_monitor_callback(float t)
{
	for (int i = 0; i < enemy_vector.size(); i++)
	{
		if (enemy_vector.at(i)->is_hited())
		{
			SimpleAudioEngine::getInstance()->playEffect("sound/bullet.wav");
			enemy_vector.at(i)->injured();
			if (enemy_vector.at(i)->is_died())
			{
				enemy_vector.at(i)->died_action();
				enemy_vector.erase(i);
			}
		}
		else if (enemy_vector.at(i)->is_impact_with_hero())
		{
			enemy_vector.at(i)->injured();
			MainGameLayer * mainlayer = dynamic_cast<MainGameLayer *>(this->getParent());
			mainlayer->_Plane_Layer->_plane->injured();
			if (enemy_vector.at(i)->is_died())
			{
				enemy_vector.at(i)->died_action();
				enemy_vector.erase(i);
			}
		}
		else if (enemy_vector.at(i)->is_out_more_of_visible())
		{
			enemy_vector.at(i)->remove_callback();
			enemy_vector.erase(i);
		}
	}
}


void Enemy_Plane_GameLayer::auto_add_enemy1(float t)
{
	schedule(SEL_SCHEDULE(&Enemy_Plane_GameLayer::add_enemy1),t);
}

void Enemy_Plane_GameLayer::auto_add_enemy2(float t)
{
	schedule(SEL_SCHEDULE(&Enemy_Plane_GameLayer::add_enemy2), t);
}

void Enemy_Plane_GameLayer::auto_add_enemy3(float t)
{
	schedule(SEL_SCHEDULE(&Enemy_Plane_GameLayer::add_enemy3), t);
}
