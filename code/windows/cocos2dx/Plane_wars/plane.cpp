#include "plane.h"
#include "Plane_GameLayer.h"
#include "MainGameLayer.h"
#include "Game_Control_layer.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

bool plane::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	this->initWithSpriteFrameName("hero1.png");
	reset_plane();
	play_plane_fly_animation();

	return true;
}


void plane::play_plane_fly_animation()
{
	Animation * plane_fly_animation = AnimationCache::getInstance()->getAnimation("plane_fly_animation");
	Animate * animate = Animate::create(plane_fly_animation);
	RepeatForever * plane_fly_animation_forever = RepeatForever::create(animate);
	this->runAction(plane_fly_animation_forever);
}

void plane::add_life()
{
	if (life_present < life_max)
	{
		life_present++;
	}
}
void plane::minus_life()
{
	life_present--;
	
}

void plane::injured()
{
	if (!is_invincible)
	{
		minus_life();
		play_plane_injured_action();
		if (is_died())
		{
			dynamic_cast<MainGameLayer *>(getParent()->getParent())->add_Game_End_Layer();
			SimpleAudioEngine::getInstance()->playEffect("sound/game_over.wav");
			died_action();
		}
		else
		{
			invincible(2);
		}
	}
}
void plane::play_plane_injured_action()
{
	dynamic_cast<MainGameLayer *>(getParent()->getParent())->_Game_Control_layer->Update_Plane_life_visible();
}
bool plane::is_died()
{
	if (life_present <= 0)
	{
		return true;
	}
	return false;
}
void plane::died_action()
{
	Animation * plane_boom_animation = AnimationCache::getInstance()->getAnimation("plane_boom_animation");
	Animate * plane_boom_animate = Animate::create(plane_boom_animation);
	CallFunc * callfunc = CallFunc::create(CC_CALLBACK_0(plane::remove_callfunc,this));
	Sequence * sequence = Sequence::createWithTwoActions(plane_boom_animate, callfunc);
	this->runAction(sequence);
}

void plane::remove_callfunc()
{
	removeFromParent();
}

void plane::invincible(float t)
{
	is_invincible = true;
	invincible_action(t);
}
void plane::invincible_action(float t)
{
	Blink *blink = CCBlink::create(1, 3);
	RepeatForever * blinkforever = RepeatForever::create(blink);
	blinkforever->setTag(invincible_action_tag);
	this->runAction(blinkforever);
	scheduleOnce(SEL_SCHEDULE(&plane::un_invincible),t);
}
void plane::un_invincible(float t)
{
	this->stopActionByTag(invincible_action_tag);
	is_invincible = false;
	this->runAction(Show::create());
}

void plane::reset_plane()
{
	Size visible = Director::getInstance()->getWinSize();
	invincible(2);
	life_present = 3;
	life_max = 3;
	this->setAnchorPoint(Vec2(0.5, 0));
	this->setPosition(visible.width*0.5, 0);
}