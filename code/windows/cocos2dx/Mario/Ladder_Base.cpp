#include "Ladder_Base.h"
#include "Game_Layer.h"
#include "Mario_Player.h"

bool Ladder_Base::init()
{
	if (!Organism::init())
	{
		return false;
	}
	set_picture();
	set_physics();
	_face_dir = Common::Face_dir::Left;

	schedule(SEL_SCHEDULE(&Ladder_Base::monitor_switch));

	return true;
}


void Ladder_Base::died_monitor(float t)
{
}

void Ladder_Base::auto_move(float t)
{
	if (_face_dir == Common::Face_dir::Left)
	{
		moveleft_ctl();
		if (_horizontal <= _horizontal_min)
		{
			_face_dir = Common::Face_dir::Right;
			_left_speed = 0;
		}
	}
	else if (_face_dir == Common::Face_dir::Right)
	{
		moveright_ctl();
		if (_horizontal >= _horizontal_max)
		{
			_face_dir = Common::Face_dir::Left;
			_right_speed = 0;
		}
	}
}


void Ladder_Base::clean()
{
	Game_Layer * layer = getgamelayer();
	layer->_organism_vec.eraseObject(this);
	layer->_labber_vec.eraseObject(this);
	removeFromParent();
}

void Ladder_Base::start_monitor()
{
	if (!_monitor_work)
	{
		//自动行走检测
		schedule(SEL_SCHEDULE(&Ladder_Base::auto_move));
		//死亡检测
		schedule(SEL_SCHEDULE(&Ladder_Base::died_monitor));

		_monitor_work = true;
	}
}
void Ladder_Base::stop_monitor()
{
	if (_monitor_work)
	{
		//自动行走检测
		unschedule(SEL_SCHEDULE(&Ladder_Base::auto_move));
		//死亡检测
		unschedule(SEL_SCHEDULE(&Ladder_Base::died_monitor));
		_monitor_work = false;
	}
}




void Ladder_Base::play_new_left_move_action()
{

}
void Ladder_Base::play_new_right_move_action()
{

}

void Ladder_Base::set_picture()
{
	Texture2D* texture = Director::getInstance()->getTextureCache()->addImage("Object/ladder.png");
	SpriteFrame* frame = SpriteFrame::createWithTexture(texture, Rect(0, 0, texture->getContentSize().width,
		texture->getContentSize().height));
	this->setSpriteFrame(frame);
}

void Ladder_Base::set_physics()
{
	_left_right_move_power = 1;
	_jump_power = 1;
	_jump_anti_power = 0.01f;
	_horizontal_max = 30;
	_horizontal_min = -30;
	_height_max = 70;
	_height_min = 0;
}

void Ladder_Base::birth(Vec2 vec)
{
	this->setPosition(vec);
	this->setAnchorPoint(Vec2(0, 0));
	getgamelayer()->_labber_vec.pushBack(this);
}
