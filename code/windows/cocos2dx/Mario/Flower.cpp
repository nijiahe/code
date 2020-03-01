#include "Flower.h"

#include "Game_Layer.h"
#include "Mario_Player.h"

bool Flower::init()
{
	if (!Organism::init())
	{
		return false;
	}
	set_picture();
	set_physics();
	_face_dir = Common::Face_dir::Left;
	setLocalZOrder(0);
	schedule(SEL_SCHEDULE(&Flower::monitor_switch));

	return true;
}

void Flower::clean()
{
	Game_Layer * layer = getgamelayer();
	layer->_enemy_vec.eraseObject(this);
	layer->_organism_vec.eraseObject(this);
	removeFromParent();
}


void Flower::auto_move(float t)
{
	if (_is_up)
	{
		_jump_speed = _jump_power;
		_up_depth += _jump_speed;
		if (_up_depth > 0)
		{
			_jump_speed = 0;
			_is_up = false;
			unschedule(SEL_SCHEDULE(&Flower::auto_move));
			
			Animate * animate = Animate::create(AnimationCache::getInstance()->getAnimation("Flower_move"));
			CallFunc * callfunc = CallFunc::create(CC_CALLBACK_0(Flower::resume_automove, this));
			this->runAction(Sequence::createWithTwoActions(Repeat::create(animate,3), callfunc));
		}
	}
	else
	{
		_down_speed = _jump_power;
		_up_depth -= _down_speed;
		if (_up_depth < -getmap()->getTileSize().height*4)
		{
			_down_speed = 0;
			_is_up = true;	
		}
	}
}

void Flower::resume_automove()
{
	schedule(SEL_SCHEDULE(&Flower::auto_move));
}

void Flower::start_monitor()
{
	if (!_monitor_work)
	{
		//上下方向速度检测
		schedule(SEL_SCHEDULE(&Flower::jump_monitor));
		//自动行走检测
		schedule(SEL_SCHEDULE(&Flower::auto_move));
		_monitor_work = true;
	}
}
void Flower::stop_monitor()
{
	if (_monitor_work)
	{
		//上下方向速度检测
		unschedule(SEL_SCHEDULE(&Flower::jump_monitor));
		//自动行走检测
		unschedule(SEL_SCHEDULE(&Flower::auto_move));
		_monitor_work = false;
	}
}

void Flower::set_picture()
{
	Texture2D* texture = Director::getInstance()->getTextureCache()->addImage("Player_and_Monster/flower0.png");
	SpriteFrame* frame = SpriteFrame::createWithTexture(texture, Rect(0, 0, texture->getContentSize().width / 2,
		texture->getContentSize().height));
	this->setSpriteFrame(frame);
}

void Flower::set_physics()
{
	_left_right_move_power = 0;
	_jump_power = 0.8f;
}

void Flower::birth(Vec2 vec)
{
	this->setPosition(vec);
	this->setAnchorPoint(Vec2(0, 0));
	getgamelayer()->_enemy_vec.pushBack(this);
	getgamelayer()->_organism_vec.pushBack(this);
}