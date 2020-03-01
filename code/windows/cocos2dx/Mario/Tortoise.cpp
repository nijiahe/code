#include "Tortoise.h"
#include "Game_Layer.h"
#include "Mario_Player.h"

bool Tortoise::init()
{
	if (!Organism::init())
	{
		return false;
	}
	set_picture();
	set_physics();
	_face_dir = Common::Face_dir::Left;

	schedule(SEL_SCHEDULE(&Tortoise::monitor_switch));

	return true;
}

void Tortoise::clean()
{
	Game_Layer * layer = getgamelayer();
	layer->_enemy_vec.eraseObject(this);
	layer->_gravitation_vec.eraseObject(this);
	layer->_organism_vec.eraseObject(this);
	layer->_tortoise_vec.eraseObject(this);
	removeFromParent();
}

void Tortoise::died_monitor(float t)
{
	Game_Layer * layer = getgamelayer();
	Mario_Player * mario = get_mario();
	if (mario->isGod)
	{
		return;
	}
	Rect next_rect = mario->getnext_Frame_boundingbox_onmap();
	float scale = 0.3f;
	Rect body_rect = Rect(next_rect.getMinX(), next_rect.getMinY() + next_rect.size.height*scale, next_rect.size.width, next_rect.size.height*(1 - scale));
	Rect foot_rect = Rect(next_rect.getMinX(), next_rect.getMinY(), next_rect.size.width, next_rect.size.height*scale);
	Rect this_next_rect = this->getnext_Frame_boundingbox_onmap();
	
	if (isGod)
	{
		this_next_rect.setRect(this_next_rect.getMinX(), this_next_rect.getMinY(), this_next_rect.size.width, this_next_rect.size.height*0.5);
	}
	else
	{
		this_next_rect.setRect(this_next_rect.getMinX(), this_next_rect.getMinY(), this_next_rect.size.width, this_next_rect.size.height);
	}

	if (!isGod)
	{
		if (this_next_rect.intersectsRect(foot_rect) && !this_next_rect.intersectsRect(body_rect))
		{
			Common::MoveNode(mario, Vec2(0, mario->getnow_Frame_boundingbox_onmap().getMinY() - this->getnow_Frame_boundingbox_onmap().getMaxY()));
			isGod = true;
			mario->_down_speed = 0;
			mario->_jump_speed = _jump_anti_power;
			stopAllActions();
			stop_monitor();
			set_picture();
			_is_moving_left = false;
			_is_moving_right = false;
			_left_speed = 0;
			_right_speed = 0;
			Animate * animate = Animate::create(AnimationCache::getInstance()->getAnimation("Tortoise_died"));
			this->runAction(RepeatForever::create(animate));
			schedule(SEL_SCHEDULE(&Tortoise::relife_monitor));
			set_God_physics();
		}
		if (collision_by_God_tortoise())
		{
			isGod = true;
			stopAllActions();
			stop_monitor();
			set_picture();
			_is_moving_left = false;
			_is_moving_right = false;
			_left_speed = 0;
			_right_speed = 0;
			Animate * animate = Animate::create(AnimationCache::getInstance()->getAnimation("Tortoise_died"));
			this->runAction(RepeatForever::create(animate));
			//重生定时器
			schedule(SEL_SCHEDULE(&Tortoise::relife_monitor));
		}
	}
	else if (isGod)
	{
		if (this_next_rect.intersectsRect(foot_rect) && !this_next_rect.intersectsRect(body_rect))
		{
			//Common::MoveNode(mario, Vec2(0, mario->getnow_Frame_boundingbox_onmap().getMinY() - this->getnow_Frame_boundingbox_onmap().getMaxY()));
			mario->_down_speed = 0;
			mario->_jump_speed = _jump_anti_power;
			if (_is_moving_left || _is_moving_right)
			{
				unschedule(SEL_SCHEDULE(&Tortoise::auto_move2));
				_is_moving_left = false;
				_is_moving_right = false;
				_left_speed = 0;
				_right_speed = 0;
			}
			else
			{
				schedule(SEL_SCHEDULE(&Tortoise::auto_move2));
				
				if (_is_moving_left)
				{
					_face_dir = Common::Face_dir::Right;
				}
				else if (_is_moving_right)
				{
					_face_dir = Common::Face_dir::Left;
				}

				if (next_rect.getMidX() < this_next_rect.getMidX() )
				{
					_face_dir = Common::Face_dir::Right;
					_right_speed = 4 * _left_right_move_power;
				}
				else
				{
					_face_dir = Common::Face_dir::Left;
					_left_speed = 4 * _left_right_move_power;
				}
			}
		}
	}
}

void Tortoise::relife_monitor(float t)
{
	if (isGod && !_is_moving_left && !_is_moving_right)
	{
		_now_relife_time += t;
		if (_now_relife_time >= _relife_time)
		{
			//重生
			relife();
			_now_relife_time = 0;
			unschedule(SEL_SCHEDULE(&Tortoise::relife_monitor));
			set_physics();
		}
	}
	else
	{
		_now_relife_time = 0;
	}
}

void Tortoise::relife()
{
	stopAllActions();
	isGod = false;
	set_picture();
	stop_monitor();
}

void Tortoise::start_monitor()
{
	if (!_monitor_work)
	{
		//上下方向速度检测
		schedule(SEL_SCHEDULE(&Tortoise::jump_monitor));
		//左右方向速度检测
		schedule(SEL_SCHEDULE(&Tortoise::move_monitor));
		//受伤死亡检测
		schedule(SEL_SCHEDULE(&Tortoise::died_monitor));
		//头顶碰撞检测
		schedule(SEL_SCHEDULE(&Organism::Top_To_Collosion_monitor));
		//自动行走检测
		if (isGod)
		{
			//schedule(SEL_SCHEDULE(&Tortoise::auto_move2));
		}
		else if (!isGod)
		{
			schedule(SEL_SCHEDULE(&Tortoise::auto_move));
		}
		_monitor_work = true;
	}
}
void Tortoise::stop_monitor()
{
	if (_monitor_work)
	{
		//上下方向速度检测
		unschedule(SEL_SCHEDULE(&Tortoise::jump_monitor));
		//左右方向速度检测
		unschedule(SEL_SCHEDULE(&Tortoise::move_monitor));
		//受伤死亡检测
		unschedule(SEL_SCHEDULE(&Tortoise::died_monitor));
		//自动行走检测
		unschedule(SEL_SCHEDULE(&Tortoise::auto_move));
		unschedule(SEL_SCHEDULE(&Tortoise::auto_move2));
		//头顶碰撞检测
		unschedule(SEL_SCHEDULE(&Organism::Top_To_Collosion_monitor));
		_monitor_work = false;
	}
}



void Tortoise::auto_move2(float t)
{
	if (_face_dir == Common::Face_dir::Left)
	{
		moveleft_ctl();
		if (will_outofmap()||left_leaning_on_something() != Common::Tile_Type::None)
		{
			_face_dir = Common::Face_dir::Right;
			_left_speed = 0;
		}
	}
	else if (_face_dir == Common::Face_dir::Right)
	{
		moveright_ctl();
		if (will_outofmap()|| right_leaning_on_something() != Common::Tile_Type::None)
		{
			_face_dir = Common::Face_dir::Left;
			_right_speed = 0;
		}
	}
}

void Tortoise::play_new_left_move_action()
{
	stopActionByTag(Common::Action_Tag::Move_Left);
	stopActionByTag(Common::Action_Tag::Move_Right);
	//stopAllActions();
	if (isGod)
	{

	}
	else
	{
		Action * action = RepeatForever::create((Animate::create(AnimationCache::getInstance()->getAnimation("Tortoise_move_left"))));
		action->setTag(Common::Action_Tag::Move_Left);
		runAction(action);
	}
	
}
void Tortoise::play_new_right_move_action()
{
	stopActionByTag(Common::Action_Tag::Move_Left);
	stopActionByTag(Common::Action_Tag::Move_Right);
	//stopAllActions();
	if (isGod)
	{

	}
	else
	{
		Action * action = RepeatForever::create((Animate::create(AnimationCache::getInstance()->getAnimation("Tortoise_move_right"))));
		action->setTag(Common::Action_Tag::Move_Right);
		runAction(action);
	}
	
}

void Tortoise::set_picture()
{
	if (!isGod)
	{
		Texture2D* texture = Director::getInstance()->getTextureCache()->addImage("Player_and_Monster/tortoise0.png");
		SpriteFrame* frame = SpriteFrame::createWithTexture(texture, Rect(36, 54, texture->getContentSize().width / 10,
			texture->getContentSize().height));
		this->setSpriteFrame(frame);
	}
	else
	{
		Texture2D* texture = Director::getInstance()->getTextureCache()->addImage("Player_and_Monster/tortoise0.png");
		SpriteFrame* frame = SpriteFrame::createWithTexture(texture, Rect(162, 180, texture->getContentSize().width / 10,
			texture->getContentSize().height));
		this->setSpriteFrame(frame);
	}
}

void Tortoise::set_God_physics()
{
	_left_right_move_power = 3.2f;
	_jump_power = 5;
	_jump_anti_power = 4.5f;
}

void Tortoise::set_physics()
{
	_left_right_move_power = 0.8f;
	_jump_power = 5;
	_jump_anti_power = 4.5f;
}



void Tortoise::birth(Vec2 vec)
{
	this->setPosition(vec);
	this->setAnchorPoint(Vec2(0, 0));
	getgamelayer()->_gravitation_vec.pushBack(this);
	getgamelayer()->_organism_vec.pushBack(this);
	getgamelayer()->_enemy_vec.pushBack(this);
	getgamelayer()->_tortoise_vec.pushBack(this);
}