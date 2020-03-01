#include "Boss.h"
#include "Game_Layer.h"
#include "Mario_Player.h"
#include "Tortoise.h"
#include "Mushroom.h"

bool Boss::init()
{
	if (!Organism::init())
	{
		return false;
	}
	set_picture();
	set_physics();
	_face_dir = Common::Face_dir::Left;

	schedule(SEL_SCHEDULE(&Boss::monitor_switch));

	return true;
}

void Boss::clean()
{
	Game_Layer * layer = getgamelayer();
	layer->_enemy_vec.eraseObject(this);
	layer->_gravitation_vec.eraseObject(this);
	layer->_organism_vec.eraseObject(this);
	removeFromParent();
}

void Boss::call_up(float t)
{
	for (int i = 0; i < _call_up_num; i++)
	{
		int num = rand() % 2;
		int num2 = rand() % 1000;
		int num3 = rand() % 1000;
		Vec2 vec = Vec2(getnow_Frame_boundingbox_onmap().getMaxX()-60+ num2 * 120 /1000, getnow_Frame_boundingbox_onmap().getMaxY() - 30 + num3 * 60 / 1000 );
		if (num == 0)
		{
			Mushroom * mushroom = Mushroom::create();
			getmap()->addChild(mushroom);
			mushroom->birth(vec);
		}
		if (num == 1)
		{
			Tortoise * tortoise = Tortoise::create();
			getmap()->addChild(tortoise);
			tortoise->birth(vec);
		}
	}
}

void Boss::died_monitor(float t)
{
	if (isGod)
	{
		return;
	}

	if (collision_by_God_tortoise())
	{
		isGod = true;
		play_God_action(2);
		schedule(SEL_SCHEDULE(&Boss::unsetGod_schedule), 2);
		_life--;
		_call_up_num++;
		if (_life <= 0)
		{
			stopAllActions();
			unschedule(SEL_SCHEDULE(&Boss::monitor_switch));
			stop_monitor();
			clean();
		}
	}
}

void Boss::start_monitor()
{
	if (!_monitor_work)
	{
		//上下方向速度检测
		schedule(SEL_SCHEDULE(&Boss::jump_monitor));
		//左右方向速度检测
		schedule(SEL_SCHEDULE(&Boss::move_monitor));
		//自动行走检测
		schedule(SEL_SCHEDULE(&Boss::auto_move));
		//自动跳跃检测
		schedule(SEL_SCHEDULE(&Boss::auto_jump),5);
		//自动召唤检测
		schedule(SEL_SCHEDULE(&Boss::call_up), 5.1f);
		//受伤死亡检测
		schedule(SEL_SCHEDULE(&Boss::died_monitor));
		//头顶碰撞检测
		schedule(SEL_SCHEDULE(&Boss::Top_To_Collosion_monitor));
		_monitor_work = true;
	}
}
void Boss::stop_monitor()
{
	if (_monitor_work)
	{
		//上下方向速度检测
		unschedule(SEL_SCHEDULE(&Boss::jump_monitor));
		//左右方向速度检测
		unschedule(SEL_SCHEDULE(&Boss::move_monitor));
		//自动行走检测
		unschedule(SEL_SCHEDULE(&Boss::auto_move));
		//自动跳跃检测
		unschedule(SEL_SCHEDULE(&Boss::auto_jump));
		//自动召唤检测
		unschedule(SEL_SCHEDULE(&Boss::call_up));
		//受伤死亡检测
		unschedule(SEL_SCHEDULE(&Boss::died_monitor));
		//头顶碰撞检测
		unschedule(SEL_SCHEDULE(&Organism::Top_To_Collosion_monitor));
		_monitor_work = false;
	}
}

void Boss::play_new_left_move_action()
{
	stopActionByTag(Common::Action_Tag::Move_Left);
	stopActionByTag(Common::Action_Tag::Move_Right);
	//stopAllActions();
	Action * action = RepeatForever::create((Animate::create(AnimationCache::getInstance()->getAnimation("Boss_move_left"))));
	action->setTag(Common::Action_Tag::Move_Left);
	runAction(action);
}
void Boss::play_new_right_move_action()
{
	stopActionByTag(Common::Action_Tag::Move_Left);
	stopActionByTag(Common::Action_Tag::Move_Right);
	//stopAllActions();
	Action * action = RepeatForever::create((Animate::create(AnimationCache::getInstance()->getAnimation("Boss_move_right"))));
	action->setTag(Common::Action_Tag::Move_Right);
	runAction(action);
}

void Boss::set_picture()
{
	Texture2D* texture = Director::getInstance()->getTextureCache()->addImage("Player_and_Monster/boss.png");
	SpriteFrame* frame = SpriteFrame::createWithTexture(texture, Rect(0, 0, texture->getContentSize().width / 8,
		texture->getContentSize().height));
	this->setSpriteFrame(frame);
}

void Boss::set_physics()
{
	_left_right_move_power = 1;
	_jump_power = 5;
	_jump_anti_power = 4.5f;
	_life = 10;
}

void Boss::birth(Vec2 vec)
{
	this->setPosition(vec);
	this->setAnchorPoint(Vec2(0, 0));
	getgamelayer()->_gravitation_vec.pushBack(this);
	getgamelayer()->_organism_vec.pushBack(this);
	getgamelayer()->_enemy_vec.pushBack(this);
}