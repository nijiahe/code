#include "FlyFish.h"
#include "Game_Layer.h"
#include "Mario_Player.h"

bool FlyFish::init()
{
	if (!Organism::init())
	{
		return false;
	}
	_color_type = rand() % 3;

	set_picture();
	set_physics();

	int num = rand() % 2;
	if (num == 0)
	{
		_face_dir = Common::Face_dir::Left;
	}
	else
	{
		_face_dir = Common::Face_dir::Right;
	}
	setVisible(false);
	schedule(SEL_SCHEDULE(&FlyFish::wake_up));

	return true;
}


void FlyFish::change_speed_monitor(float t)
{
	_jump_power = (rand_0_1()*0.5 + 0.5)*_origin_jump_power;
	_left_right_move_power = (rand_0_1()*0.5 + 0.5)*_origin_left_right_move_power;
}

void FlyFish::jump_monitor(float t)
{
	if (this->_jump_speed > 0)
	{
		_height += this->_jump_speed;
		Common::MoveNode(this, Vec2(0, this->_jump_speed));
	}
	else if (this->_down_speed > 0)
	{
		_height -= this->_down_speed;
		Common::MoveNode(this, Vec2(0, -this->_down_speed));
	}
}

void FlyFish::wake_up(float t)
{
	if (!_is_sleep)
	{
		return;
	}
	Rect rect = get_mario()->getnow_Frame_boundingbox_onmap();
	Rect res_rect = Rect(rect.getMinX() , rect.getMinY() - Winsize.height*0.5, rect.size.width, Winsize.height);
	if (res_rect.intersectsRect(this->getnow_Frame_boundingbox_onmap()))
	{
		setVisible(true);
		schedule(SEL_SCHEDULE(&FlyFish::monitor_switch));
		scheduleOnce(SEL_SCHEDULE(&FlyFish::sleep), 5);
		_is_sleep = false;
	}
}

void FlyFish::sleep(float t)
{
	setVisible(false);
	unschedule(SEL_SCHEDULE(&FlyFish::monitor_switch));
	stop_monitor();
	_is_sleep = true;
}

void FlyFish::unset_rest(float t)
{
	_rest = false;
}

void FlyFish::auto_move(float t)
{
	if (_rest)
	{
		return;
	}
	if (!_is_down)
	{
		if (_face_dir == Common::Face_dir::Left)
		{
			moveleft_ctl();
			
			_jump_speed = _jump_power;
			if (will_outofmap()|| _height>=_max_height)
			{
				_face_dir = Common::Face_dir::Right;
				_left_speed = 0;
				_jump_speed = 0; 
				_is_down = true;
				_rest = true;
				scheduleOnce(SEL_SCHEDULE(&FlyFish::unset_rest), 1);
			}
		}
		else if (_face_dir == Common::Face_dir::Right)
		{
			moveright_ctl();
			_jump_speed = _jump_power;
			if (will_outofmap() || _height >= _max_height)
			{
				_face_dir = Common::Face_dir::Left;
				_right_speed = 0;
				_jump_speed = 0;
				_is_down = true;
				_rest = true;
				scheduleOnce(SEL_SCHEDULE(&FlyFish::unset_rest), 1);
			}
		}
	}
	else
	{
		if (_face_dir == Common::Face_dir::Left)
		{
			moveleft_ctl();
			_down_speed = _jump_power;
			if (will_outofmap() || _height <= 0)
			{
				_face_dir = Common::Face_dir::Right;
				_left_speed = 0;
				_down_speed = 0;
				_is_down = false;
				_rest = true;
				scheduleOnce(SEL_SCHEDULE(&FlyFish::unset_rest), 1);
			}
		}
		else if (_face_dir == Common::Face_dir::Right)
		{
			moveright_ctl();
			_down_speed = _jump_power;
			if (will_outofmap() || _height <= 0)
			{
				_face_dir = Common::Face_dir::Left;
				_right_speed = 0;
				_down_speed = 0;
				_is_down = false;
				_rest = true;
				scheduleOnce(SEL_SCHEDULE(&FlyFish::unset_rest), 1);
			}
		}
	}
	
}

void FlyFish::clean()
{
	Game_Layer * layer = getgamelayer();
	layer->_enemy_vec.eraseObject(this);
	layer->_organism_vec.eraseObject(this);
	removeFromParent();
}

void FlyFish::start_monitor()
{
	if (!_monitor_work)
	{
		//上下方向速度检测
		schedule(SEL_SCHEDULE(&FlyFish::jump_monitor));
		//左右方向速度检测
		schedule(SEL_SCHEDULE(&FlyFish::move_monitor));
		//自动行走检测
		schedule(SEL_SCHEDULE(&FlyFish::auto_move));
		//自动改变速度检测
		schedule(SEL_SCHEDULE(&FlyFish::change_speed_monitor),1);
		_monitor_work = true;
	}
}
void FlyFish::stop_monitor()
{
	if (_monitor_work)
	{
		//上下方向速度检测
		unschedule(SEL_SCHEDULE(&FlyFish::jump_monitor));
		//左右方向速度检测
		unschedule(SEL_SCHEDULE(&FlyFish::move_monitor));
		//自动行走检测
		unschedule(SEL_SCHEDULE(&FlyFish::auto_move));
		//自动改变速度检测
		unschedule(SEL_SCHEDULE(&FlyFish::change_speed_monitor));
		
		_monitor_work = false;
	}
}




void FlyFish::play_new_left_move_action()
{
	stopActionByTag(Common::Action_Tag::Move_Left);
	stopActionByTag(Common::Action_Tag::Move_Right);
	char action_name[30];
	sprintf(action_name, "%s%d", "flyfish_move_left", _color_type);
	//stopAllActions();
	Action * action = RepeatForever::create((Animate::create(AnimationCache::getInstance()->getAnimation(action_name))));
	action->setTag(Common::Action_Tag::Move_Left);
	runAction(action);
}
void FlyFish::play_new_right_move_action()
{
	stopActionByTag(Common::Action_Tag::Move_Left);
	stopActionByTag(Common::Action_Tag::Move_Right);
	char action_name[30];
	sprintf(action_name, "%s%d", "flyfish_move_right", _color_type);
	//stopAllActions();
	Action * action = RepeatForever::create((Animate::create(AnimationCache::getInstance()->getAnimation(action_name))));
	action->setTag(Common::Action_Tag::Move_Right);
	runAction(action);
}

void FlyFish::set_picture()
{
	if (_face_dir == Common::Face_dir::Left)
	{
		if (_color_type == 0)
		{
			Texture2D* texture = Director::getInstance()->getTextureCache()->addImage("Player_and_Monster/flyFishRight.png");
			SpriteFrame* frame = SpriteFrame::createWithTexture(texture, Rect(0, 0, texture->getContentSize().width / 6,
				texture->getContentSize().height));
			this->setSpriteFrame(frame);
		}
		else if (_color_type == 1)
		{
			Texture2D* texture = Director::getInstance()->getTextureCache()->addImage("Player_and_Monster/flyFishRight.png");
			SpriteFrame* frame = SpriteFrame::createWithTexture(texture, Rect(texture->getContentSize().width / 6*2, 0, texture->getContentSize().width / 6,
				texture->getContentSize().height));
			this->setSpriteFrame(frame);
		}
		else if (_color_type == 2)
		{
			Texture2D* texture = Director::getInstance()->getTextureCache()->addImage("Player_and_Monster/flyFishRight.png");
			SpriteFrame* frame = SpriteFrame::createWithTexture(texture, Rect(texture->getContentSize().width / 6*4, 0, texture->getContentSize().width / 6,
				texture->getContentSize().height));
			this->setSpriteFrame(frame);
		}
	}
	else
	{
		if (_color_type == 0)
		{
			Texture2D* texture = Director::getInstance()->getTextureCache()->addImage("Player_and_Monster/flyFishRight.png");
			SpriteFrame* frame = SpriteFrame::createWithTexture(texture, Rect(0, 0, texture->getContentSize().width / 6,
				texture->getContentSize().height));
			this->setSpriteFrame(frame);
		}
		else if (_color_type == 1)
		{
			Texture2D* texture = Director::getInstance()->getTextureCache()->addImage("Player_and_Monster/flyFishRight.png");
			SpriteFrame* frame = SpriteFrame::createWithTexture(texture, Rect(texture->getContentSize().width / 6*2, 0, texture->getContentSize().width / 6,
				texture->getContentSize().height));
			this->setSpriteFrame(frame);
		}
		else if (_color_type == 2)
		{
			Texture2D* texture = Director::getInstance()->getTextureCache()->addImage("Player_and_Monster/flyFishRight.png");
			SpriteFrame* frame = SpriteFrame::createWithTexture(texture, Rect(texture->getContentSize().width / 6*4, 0, texture->getContentSize().width / 6,
				texture->getContentSize().height));
			this->setSpriteFrame(frame);
		}
	}
}

void FlyFish::set_physics()
{
	_left_right_move_power = 2;
	_jump_power = 3;
	_jump_anti_power = 4.5f;
	_max_height = Winsize.height*( 0.4 + 0.4*rand_0_1());
	_origin_left_right_move_power = _left_right_move_power;
	_origin_jump_power = _jump_power;
}



void FlyFish::birth(Vec2 vec)
{
	this->setPosition(vec);
	this->setAnchorPoint(Vec2(0, 0));
	getgamelayer()->_enemy_vec.pushBack(this);
	getgamelayer()->_organism_vec.pushBack(this);
}