#include "enemy.h"
#include "MainGameLayer.h"
#include "Enemy_Plane_GameLayer.h"
#include "Bullet_GameLayer.h"
#include "plane.h"
#include "Plane_GameLayer.h"

bool enemy::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	init_with_picture();

	return true;
}

void enemy::init_with_picture()
{

}
void enemy::play_plane_boom_animation()
{

}
void enemy::play_plane_injured_action()
{

}

void enemy::enemy_fly_action()
{

}
void enemy::enemy_shoot_action(float t)
{

}

void enemy::run_enemy_shoot_aciont()
{

}

void enemy::init_fly_speed()
{

}

void enemy::minus_life()
{
	life_present--;
}

void enemy::injured()
{
	minus_life();
	if (!is_died())
	{
		play_plane_injured_action();
	}
}

bool enemy::is_hited()
{
	MainGameLayer * mainlayer = dynamic_cast<MainGameLayer *>((dynamic_cast<Enemy_Plane_GameLayer*>(getParent()))->getParent());
	for (int i = 0; i < mainlayer->_Bullet_Layer->bullet_vector.size(); i++)
	{
		if (this->getBoundingBox().intersectsRect(mainlayer->_Bullet_Layer->bullet_vector.at(i)->getBoundingBox()))
		{
			mainlayer->_Bullet_Layer->bullet_vector.at(i)->removeFromParent();
			mainlayer->_Bullet_Layer->bullet_vector.erase(i);
			return true;
		}
	}
	return false;
}

bool enemy::is_died()
{
	if (life_present <= 0)
	{
		return true;
	}
	return false;
}

bool enemy::is_impact_with_hero()
{
	MainGameLayer * mainlayer = dynamic_cast<MainGameLayer *>((dynamic_cast<Enemy_Plane_GameLayer*>(getParent()))->getParent());
	if (!mainlayer->_Plane_Layer->_plane->is_died())
	{
		if (mainlayer->_Plane_Layer->_plane->getBoundingBox().intersectsRect(this->getBoundingBox()))
		{
			return true;
		}
	}
	return false;
}

bool enemy::is_out_more_of_visible()
{
	Size visible = Director::getInstance()->getWinSize();
	if (this->getPositionY() <= -visible.height*0.5)
	{
		return true;
	}
	return false;
}

void enemy::died_action()
{
	Animation * plane_boom_animation = AnimationCache::getInstance()->getAnimation("enemy1_boom_animation");
	Animate * plane_boom_animate = Animate::create(plane_boom_animation);
	CallFunc * callfunc = CallFunc::create(CC_CALLBACK_0(enemy::remove_callback, this));
	Sequence * sequence = Sequence::createWithTwoActions(plane_boom_animate, callfunc);
	this->runAction(sequence);
}

void enemy::remove_callback()
{
	this->removeFromParent();
}

void enemy::reset_plane()
{
	Size visible = Director::getInstance()->getWinSize();
	life_present = 3;
	life_max = 3;
}
