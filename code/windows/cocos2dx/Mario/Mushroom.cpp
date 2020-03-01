#include "Mushroom.h"
#include "Game_Layer.h"
#include "Mario_Player.h"

bool Mushroom::init()
{
	if (!Organism::init())
	{
		return false;
	}
	set_picture();
	set_physics();
	_face_dir = Common::Face_dir::Left;

	schedule(SEL_SCHEDULE(&Mushroom::monitor_switch));

	return true;
}

void Mushroom::clean()
{
	Game_Layer * layer = getgamelayer();
	layer->_enemy_vec.eraseObject(this);
	layer->_gravitation_vec.eraseObject(this);
	layer->_organism_vec.eraseObject(this);
	removeFromParent();
}

void Mushroom::died_monitor(float t)
{
	Game_Layer * layer = getgamelayer();
	Rect next_rect = get_mario()->getnext_Frame_boundingbox_onmap();
	float scale = 0.5f;
	Rect body_rect = Rect(next_rect.getMinX(), next_rect.getMinY() + next_rect.size.height*scale, next_rect.size.width, next_rect.size.height*(1 - scale));
	Rect foot_rect = Rect(next_rect.getMinX(), next_rect.getMinY() , next_rect.size.width, next_rect.size.height*scale);
	

	if (this->getnext_Frame_boundingbox_onmap().intersectsRect(foot_rect) &&
		!this->getnext_Frame_boundingbox_onmap().intersectsRect(body_rect))
	{
		isGod = true;
		get_mario()->_down_speed = 0;
		get_mario()->_jump_speed = _jump_anti_power;
		stopAllActions();
		unschedule(SEL_SCHEDULE(&Mushroom::monitor_switch));
		stop_monitor();
		Animate * animate = Animate::create(AnimationCache::getInstance()->getAnimation("Mushroom_died"));
		CallFunc * callfunc = CallFunc::create(CC_CALLBACK_0(Mushroom::clean,this));
		this->runAction(Sequence::createWithTwoActions(animate, callfunc));
		SimpleAudioEngine::getInstance()->playEffect("Sounds/CaiSiGuaiWu.ogg");
	}
	if (collision_by_God_tortoise())
	{
		isGod = true;
		stopAllActions();
		unschedule(SEL_SCHEDULE(&Mushroom::monitor_switch));
		stop_monitor();
		Animate * animate = Animate::create(AnimationCache::getInstance()->getAnimation("Mushroom_died"));
		CallFunc * callfunc = CallFunc::create(CC_CALLBACK_0(Mushroom::clean, this));
		this->runAction(Sequence::createWithTwoActions(animate, callfunc));
	}
}

void Mushroom::start_monitor()
{
	if (!_monitor_work)
	{
		//上下方向速度检测
		schedule(SEL_SCHEDULE(&Mushroom::jump_monitor));
		//左右方向速度检测
		schedule(SEL_SCHEDULE(&Mushroom::move_monitor));
		//受伤死亡检测
		schedule(SEL_SCHEDULE(&Mushroom::died_monitor));
		//自动行走检测
		schedule(SEL_SCHEDULE(&Mushroom::auto_move));
		//头顶碰撞检测
		schedule(SEL_SCHEDULE(&Organism::Top_To_Collosion_monitor));
		_monitor_work = true;
	}
}
void Mushroom::stop_monitor()
{
	if (_monitor_work)
	{
		//上下方向速度检测
		unschedule(SEL_SCHEDULE(&Mushroom::jump_monitor));
		//左右方向速度检测
		unschedule(SEL_SCHEDULE(&Mushroom::move_monitor));
		//受伤死亡检测
		unschedule(SEL_SCHEDULE(&Mushroom::died_monitor));
		//自动行走检测
		unschedule(SEL_SCHEDULE(&Mushroom::auto_move));
		//头顶碰撞检测
		unschedule(SEL_SCHEDULE(&Organism::Top_To_Collosion_monitor));
		_monitor_work = false;
	}
}




void Mushroom::play_new_left_move_action()
{
	stopActionByTag(Common::Action_Tag::Move_Left);
	stopActionByTag(Common::Action_Tag::Move_Right);
	//stopAllActions();
	Action * action = RepeatForever::create((Animate::create(AnimationCache::getInstance()->getAnimation("Mushroom_move_left"))));
	action->setTag(Common::Action_Tag::Move_Left);
	runAction(action);
}
void Mushroom::play_new_right_move_action()
{
	stopActionByTag(Common::Action_Tag::Move_Left);
	stopActionByTag(Common::Action_Tag::Move_Right);
	//stopAllActions();
	Action * action = RepeatForever::create((Animate::create(AnimationCache::getInstance()->getAnimation("Mushroom_move_right"))));
	action->setTag(Common::Action_Tag::Move_Right);
	runAction(action);
}

void Mushroom::set_picture()
{
	Texture2D* texture = Director::getInstance()->getTextureCache()->addImage("Player_and_Monster/Mushroom0.png");
	SpriteFrame* frame = SpriteFrame::createWithTexture(texture, Rect(0, 0, texture->getContentSize().width / 4,
		texture->getContentSize().height));
	this->setSpriteFrame(frame);
}

void Mushroom::set_physics()
{
	_left_right_move_power = 1;
	_jump_power = 4;
	_jump_anti_power = 4.5f;
}

void Mushroom::birth(Vec2 vec)
{
	this->setPosition(vec);
	this->setAnchorPoint(Vec2(0, 0));
	getgamelayer()->_gravitation_vec.pushBack(this);
	getgamelayer()->_organism_vec.pushBack(this);
	getgamelayer()->_enemy_vec.pushBack(this);
}