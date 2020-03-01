#include "Mario_Player.h"
#include "Game_Layer.h"
#include "Mushroom_Reward.h"
#include "LadderLR_Sprite.h"

bool Mario_Player::init()
{
	if (!Organism::init())
	{
		return false;
	}
	set_picture();
	set_physics();

	run_monitor_switch();

	return true;
}

void Mario_Player::auto_move(float t)
{
	Game_Layer * layer = getgamelayer();

	TMXTiledMap * map = getmap();
	Rect rect = layer->_finalpoint->getBoundingBox();
	Vec2 origin_place = Vec2(rect.getMinX(), rect.getMinY());
	Rect final_point_rect = Rect(origin_place, this->getContentSize());

	Rect mario_rect = getnow_Frame_boundingbox_onmap();
	if (mario_rect.getMidX() - final_point_rect.getMidX() < -3)
	{
		moveright_ctl();
	}
	else if (mario_rect.getMidX() - final_point_rect.getMidX() > 3)
	{
		moveleft_ctl();
	}
	else if (final_point_rect.getMinY() > mario_rect.getMidY())
	{
		this->_jump_speed = this->_jump_power;
	}
}

void Mario_Player::run_automove()
{
	schedule(SEL_SCHEDULE(&Mario_Player::auto_move));
}

void Mario_Player::stop_automove()
{
	unschedule(SEL_SCHEDULE(&Mario_Player::auto_move));
}

bool Mario_Player::inspect_mushroom_reward(Sprite * spr)
{
	Game_Layer * layer = getgamelayer();
	for (int i = 0; i < layer->_reward_vec.size(); i++)
	{
		Mushroom_Reward * reward = layer->_reward_vec.at(i);
		if (spr->getBoundingBox().intersectsRect(reward->getBoundingBox())&& reward->_Sleep)
		{
			reward->wakeup();
			return true;
		}
	}
	return false;
}

void Mario_Player::Top_To_Collosion_monitor(float t)
{
	if (will_outofmap())
	{
		this->_jump_speed = 0;
		return;
	}
	Common::Tile_Type tile_type1 = this->Left_Top_To_something();
	Common::Tile_Type tile_type2 = this->Right_Top_To_something();
	if (tile_type1 == Common::Tile_Type::Land)
	{
		tile_type1 = Common::Tile_Type::None;
	}
	if (tile_type2 == Common::Tile_Type::Land)
	{
		tile_type2 = Common::Tile_Type::None;
	}
	if (tile_type1 == Common::Tile_Type::None && tile_type2 == Common::Tile_Type::None)
	{
		return;
	}
	
	this->_jump_speed = 0;

	Sprite * left = get_Left_Top_to();
	Sprite * right = get_Right_Top_to();

	if (!_iseatMushroom)
	{
		if (tile_type1 == Common::Tile_Type::Tub_Block&&left)
		{
			left->runAction(JumpBy::create(0.5, Vec2(0, 0), 20, 1));
		}
		else if (tile_type1 == Common::Tile_Type::Solid_Block&&left)
		{
			if (inspect_mushroom_reward(left))
			{
				Vec2 left = get_Next_Frame_Left_Head_Tile_Positon();
				getmap()->getLayer("block")->setTileGID(1 * 30 + 1, left);
			}
		}

		if (tile_type2 == Common::Tile_Type::Tub_Block&&right)
		{
			right->runAction(JumpBy::create(0.5, Vec2(0, 0), 20, 1));
		}
		else if (tile_type2 == Common::Tile_Type::Solid_Block&&right)
		{
			if (inspect_mushroom_reward(right))
			{
				Vec2 right = get_Next_Frame_Right_Head_Tile_Positon();
				getmap()->getLayer("block")->setTileGID(1 * 30 + 1, right);
			}
		}
	}
	//³ÔÁËÄ¢¹½
	else
	{
		if (tile_type1 == Common::Tile_Type::Tub_Block&&left)
		{
			Vec2 left = get_Next_Frame_Left_Head_Tile_Positon();
			getmap()->getLayer("block")->setTileGID(12, left);
		}
		else if (tile_type1 == Common::Tile_Type::Solid_Block&&left)
		{
			if (inspect_mushroom_reward(left))
			{
				Vec2 left = get_Next_Frame_Left_Head_Tile_Positon();
				getmap()->getLayer("block")->setTileGID(1 * 30 + 1, left);
			}
		}

		if (tile_type2 == Common::Tile_Type::Tub_Block&&right)
		{
			Vec2 right = get_Next_Frame_Right_Head_Tile_Positon();
			getmap()->getLayer("block")->setTileGID(12, right);
		}
		else if (tile_type2 == Common::Tile_Type::Solid_Block&&right)
		{
			if (inspect_mushroom_reward(right))
			{
				Vec2 right = get_Next_Frame_Right_Head_Tile_Positon();
				getmap()->getLayer("block")->setTileGID(1 * 30 + 1, right);
			}
		}
	}
}

void Mario_Player::run_monitor_switch()
{
	schedule(SEL_SCHEDULE(&Mario_Player::monitor_switch));
}

void Mario_Player::start_monitor()
{
	if (!_monitor_work)
	{
		//ÉÏÏÂ·½ÏòËÙ¶È¼ì²â
		schedule(SEL_SCHEDULE(&Mario_Player::jump_monitor));
		//×óÓÒ·½ÏòËÙ¶È¼ì²â
		schedule(SEL_SCHEDULE(&Mario_Player::move_monitor));
		//ÊÜÉËËÀÍö¼ì²â
		schedule(SEL_SCHEDULE(&Mario_Player::died_monitor));
		//Í·¶¥Åö×²¼ì²â
		schedule(SEL_SCHEDULE(&Mario_Player::Top_To_Collosion_monitor));
		//Åöµ½Æì¸Ë¼ì²â
		schedule(SEL_SCHEDULE(&Mario_Player::touch_Flagpole_monitor));
		//³Ô½ð±Ò¼ì²â
		schedule(SEL_SCHEDULE(&Mario_Player::eat_coin));
		_monitor_work = true;
	}
}

void Mario_Player::stop_monitor()
{
	if (_monitor_work)
	{
		//ÉÏÏÂ·½ÏòËÙ¶È¼ì²â
		unschedule(SEL_SCHEDULE(&Mario_Player::jump_monitor));
		//×óÓÒ·½ÏòËÙ¶È¼ì²â
		unschedule(SEL_SCHEDULE(&Mario_Player::move_monitor));
		//ÊÜÉËËÀÍö¼ì²â
		unschedule(SEL_SCHEDULE(&Mario_Player::died_monitor));
		//Í·¶¥Åö×²¼ì²â
		unschedule(SEL_SCHEDULE(&Mario_Player::Top_To_Collosion_monitor));
		//Åöµ½Æì¸Ë¼ì²â
		unschedule(SEL_SCHEDULE(&Mario_Player::touch_Flagpole_monitor));
		//³Ô½ð±Ò¼ì²â
		unschedule(SEL_SCHEDULE(&Mario_Player::eat_coin));
		_monitor_work = false;
	}
}

void Mario_Player::touch_Flagpole_monitor(float t)
{
	if (left_leaning_on_something() == Common::Tile_Type::Flagpole || right_leaning_on_something() == Common::Tile_Type::Flagpole)
	{
		stopAllActions();
		_left_speed = 0;
		_right_speed = 0;

		_is_moving_left = false;
		_is_moving_right = false;

		_touch_Flagpole = true;
	}
}

void Mario_Player::eat_coin(float t)
{
	TMXLayer * layer = getmap()->getLayer("coin");
	Rect now_Frame_boundingbox = getnow_Frame_boundingbox_onmap();
	Vec2 body[4];
	body[0] = Vec2(now_Frame_boundingbox.getMinX(), now_Frame_boundingbox.getMinY());
	body[1] = Vec2(now_Frame_boundingbox.getMaxX(), now_Frame_boundingbox.getMinY());
	body[2] = Vec2(now_Frame_boundingbox.getMinX(), now_Frame_boundingbox.getMaxY());
	body[3] = Vec2(now_Frame_boundingbox.getMaxX(), now_Frame_boundingbox.getMaxY());
	for (int i = 0; i < 4; i++)
	{
		Vec2 map_body = Convert_To_Map_Position(body[i]);
		int gid = layer->getTileGIDAt(map_body);
		Common::Tile_Type type = Common::Convert_Gid_To_Type(gid);
		if (type == Common::Tile_Type::Coin)
		{
			SimpleAudioEngine::getInstance()->playEffect("Sounds/EatCoin.wma");
			_coin_count++;
			layer->setTileGID(12, map_body);
		}
	}
	
}

void Mario_Player::died_monitor(float t)
{
	if (isGod)
	{
		return;
	}
	Game_Layer * layer = getgamelayer();
	Rect now_rect = getnow_Frame_boundingbox_onmap();
	//now_rect.setRect(now_rect.getMinX(), now_rect.getMinY(), now_rect.size.width, now_rect.size.height);
	for (int i = 0; i < layer->_enemy_vec.size(); i++)
	{
		Organism * organism = layer->_enemy_vec.at(i);
		if (organism->isGod)
		{
			continue;
		}
		Rect enemy_rect = organism->getnow_Frame_boundingbox_onmap();
		if (enemy_rect.intersectsRect(now_rect))
		{
			this->isGod = true;
			scheduleOnce(SEL_SCHEDULE(&Mario_Player::unsetGod_schedule), 5);
			if (_iseatMushroom)
			{
				_iseatMushroom = false;
				set_physics();
				set_picture();
				isGod = true;
				_is_moving_left = false;
				_is_moving_right = false;
				scheduleOnce(SEL_SCHEDULE(&Mario_Player::unsetGod_schedule), _God_Time);
				play_God_action(_God_Time);
				scheduleOnce(SEL_SCHEDULE(&Mario_Player::un_God_action), _God_Time);
				
			}
			else
			{
				stopAllActions();
				runAction(Animate::create(AnimationCache::getInstance()->getAnimation("red_small_mario_died")));
				unschedule(SEL_SCHEDULE(&Mario_Player::monitor_switch));
				stop_monitor();
				_is_died = true;
			}
		}
	}
}

void Mario_Player::play_new_left_move_action()
{
	stopActionByTag(Common::Action_Tag::Move_Left);
	stopActionByTag(Common::Action_Tag::Move_Right);
	//stopAllActions();
	Action * action;
	
	if (_iseatMushroom)
	{
		action = RepeatForever::create((Animate::create(AnimationCache::getInstance()->getAnimation("red_Big_mario_move_left"))));
	}
	else
	{
		action = RepeatForever::create((Animate::create(AnimationCache::getInstance()->getAnimation("red_small_mario_move_left"))));
	}
	action->setTag(Common::Action_Tag::Move_Left);
	runAction(action);
}

void Mario_Player::play_new_right_move_action()
{
	stopActionByTag(Common::Action_Tag::Move_Left);
	stopActionByTag(Common::Action_Tag::Move_Right);
	//stopAllActions();
	Action * action;
	if (_iseatMushroom)
	{
		action = RepeatForever::create((Animate::create(AnimationCache::getInstance()->getAnimation("red_Big_mario_move_right"))));
	}
	else
	{
		action = RepeatForever::create((Animate::create(AnimationCache::getInstance()->getAnimation("red_small_mario_move_right"))));
	}
	action->setTag(Common::Action_Tag::Move_Right);
	runAction(action);
}

void Mario_Player::set_picture()
{
	Texture2D * texture;
	SpriteFrame* frame;
	if (_iseatMushroom)
	{
		if (_face_dir == Common::Face_dir::Left)
		{
			texture = Director::getInstance()->getTextureCache()->addImage("Player_and_Monster/walkLeft.png");
			frame = SpriteFrame::createWithTexture(texture, Rect(0, 0, texture->getContentSize().width / 11,
				texture->getContentSize().height));
		}
		else if (_face_dir == Common::Face_dir::Right)
		{
			texture = Director::getInstance()->getTextureCache()->addImage("Player_and_Monster/walkRight.png");
			frame = SpriteFrame::createWithTexture(texture, Rect(0, 0, texture->getContentSize().width / 11,
				texture->getContentSize().height));
		}
	}
	else
	{
		if (_face_dir == Common::Face_dir::Left)
		{
			texture = Director::getInstance()->getTextureCache()->addImage("Player_and_Monster/walkLeft.png");
			frame = SpriteFrame::createWithTexture(texture, Rect(0, 0, texture->getContentSize().width / 11,
				texture->getContentSize().height));
		}
		else if (_face_dir == Common::Face_dir::Right)
		{
			texture = Director::getInstance()->getTextureCache()->addImage("Player_and_Monster/walkRight.png");
			frame = SpriteFrame::createWithTexture(texture, Rect(0, 0, texture->getContentSize().width / 11,
				texture->getContentSize().height));
		}
	}
	this->setSpriteFrame(frame);
}



void Mario_Player::un_God_action(float t)
{
	stopActionByTag(Common::Action_Tag::God_Action);
	setVisible(true);
}

void Mario_Player::set_eatMushroom_physics()
{
	_left_right_move_power = 3;
	_jump_power = 9;
	_jump_anti_power = 0;
}

void Mario_Player::set_physics()
{
	_left_right_move_power = 2.5f;
	_jump_power = 8.0f;
	_jump_anti_power = 0;
}

void Mario_Player::clean()
{

}
void Mario_Player::birth(Vec2 vec)
{
	this->setPosition(vec);
	this->setAnchorPoint(Vec2(0, 0));
	getgamelayer()->_gravitation_vec.pushBack(this);
	getgamelayer()->_organism_vec.pushBack(this);
}

