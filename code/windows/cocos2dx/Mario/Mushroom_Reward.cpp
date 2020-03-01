#include "Mushroom_Reward.h"
#include "Game_Layer.h"
#include "Mario_Player.h"

bool Mushroom_Reward::init()
{
	if (!Organism::init())
	{
		return false;
	}
	set_picture();
	set_physics();
	_face_dir = Common::Face_dir::Left;


	return true;
}

void Mushroom_Reward::start_monitor_switch()
{
	setLocalZOrder(100);
	schedule(SEL_SCHEDULE(&Mushroom_Reward::monitor_switch));
}

void Mushroom_Reward::auto_move(float t)
{
	if (_face_dir == Common::Face_dir::Left)
	{
		moveleft_ctl();
		if (will_outofmap())
		{
			_face_dir = Common::Face_dir::Right;
			_left_speed = 0;
		}
	}
	else if (_face_dir == Common::Face_dir::Right)
	{
		moveright_ctl();
		if (will_outofmap())
		{
			_face_dir = Common::Face_dir::Left;
			_right_speed = 0;
		}
	}
}

void Mushroom_Reward::wakeup()
{
	if (_Sleep)
	{
		_Sleep = false;
		int num = rand() % 2;
		if (num == 0)
		{
			_face_dir = Common::Face_dir::Left;
		}
		else
		{
			_face_dir = Common::Face_dir::Right;
		}
		SimpleAudioEngine::getInstance()->playEffect("Sounds/DingChuMoGuHuoHua.ogg");
		MoveBy * moveby = MoveBy::create(0.5, Vec2(0, getmap()->getTileSize().height));
		CallFunc * func = CallFunc::create(CC_CALLBACK_0(Mushroom_Reward::start_monitor_switch, this));
		Sequence * seq = Sequence::createWithTwoActions(moveby, func);
		this->runAction(seq);
	}
}

void Mushroom_Reward::clean()
{
	Game_Layer * layer = getgamelayer();
	layer->_gravitation_vec.eraseObject(this);
	layer->_organism_vec.eraseObject(this);
	layer->_reward_vec.eraseObject(this);
	removeFromParent();
}

void Mushroom_Reward::died_monitor(float t)
{
	Game_Layer * layer = getgamelayer();
	Rect next_rect = get_mario()->getnext_Frame_boundingbox_onmap();

	if (this->getnext_Frame_boundingbox_onmap().intersectsRect(next_rect))
	{
		isGod = true;
		SimpleAudioEngine::getInstance()->playEffect("Sounds/EatMushroomOrFlower.ogg");
		get_mario()->_iseatMushroom = true;
		get_mario()->set_picture();
		if (get_mario()->_is_moving_left = true)
		{
			get_mario()->play_new_left_move_action();
		}
		else if (get_mario()->_is_moving_right = true)
		{
			get_mario()->play_new_right_move_action();
		}
		
		get_mario()->_is_moving_right = false;
		unschedule(SEL_SCHEDULE(&Mushroom_Reward::monitor_switch));
		stop_monitor();
		clean();
	}
}

void Mushroom_Reward::start_monitor()
{
	if (!_monitor_work)
	{
		//上下方向速度检测
		schedule(SEL_SCHEDULE(&Mushroom_Reward::jump_monitor));
		//左右方向速度检测
		schedule(SEL_SCHEDULE(&Mushroom_Reward::move_monitor));
		//受伤死亡检测
		schedule(SEL_SCHEDULE(&Mushroom_Reward::died_monitor));
		//自动行走检测
		schedule(SEL_SCHEDULE(&Mushroom_Reward::auto_move));
		//头顶碰撞检测
		schedule(SEL_SCHEDULE(&Organism::Top_To_Collosion_monitor));
		_monitor_work = true;
	}
}
void Mushroom_Reward::stop_monitor()
{
	if (_monitor_work)
	{
		//上下方向速度检测
		unschedule(SEL_SCHEDULE(&Mushroom_Reward::jump_monitor));
		//左右方向速度检测
		unschedule(SEL_SCHEDULE(&Mushroom_Reward::move_monitor));
		//受伤死亡检测
		unschedule(SEL_SCHEDULE(&Mushroom_Reward::died_monitor));
		//自动行走检测
		unschedule(SEL_SCHEDULE(&Mushroom_Reward::auto_move));
		//头顶碰撞检测
		unschedule(SEL_SCHEDULE(&Organism::Top_To_Collosion_monitor));
		_monitor_work = false;
	}
}

void Mushroom_Reward::play_new_left_move_action()
{
	
}
void Mushroom_Reward::play_new_right_move_action()
{
	
}

void Mushroom_Reward::set_picture()
{
	Texture2D* texture = Director::getInstance()->getTextureCache()->addImage("Object/rewardMushroomSet.png");

	SpriteFrame* frame = SpriteFrame::createWithTexture(texture, Rect(0, 0, texture->getContentSize().width / 3,
		texture->getContentSize().height));
	this->setSpriteFrame(frame);
}

void Mushroom_Reward::set_physics()
{
	_left_right_move_power = 1;
	_jump_power = 4;
	_jump_anti_power = 4.5f;
}


void Mushroom_Reward::birth(Vec2 vec)
{
	this->setPosition(vec);
	this->setContentSize(getmap()->getTileSize());
	this->setLocalZOrder(0);
	this->setAnchorPoint(Vec2(0, 0));
	getgamelayer()->_gravitation_vec.pushBack(this);
	getgamelayer()->_organism_vec.pushBack(this);
	getgamelayer()->_reward_vec.pushBack(this);
}