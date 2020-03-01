#include "Game_Layer.h"
#include "MenuCtl.h"
#include "Mario_Player.h"
#include "Mushroom.h"
#include "Tortoise.h"
#include "Flower.h"
#include "Grounds_Select_Layer.h"
#include "Mushroom_Reward.h"
#include "LadderLR_Sprite.h"
#include "LadderUD_Sprite.h"
#include "FlyFish.h"
#include "Boss.h"

bool Game_Layer::init(int idx, Mario_Player * mario)
{
	if (!Layer::init())
	{
		return false;
	}
	//地图
	_mario = mario;
	
	_idx = idx;
	_map = TMXTiledMap::create(Common::format("Rounds/MarioMap",idx,".tmx"));
	
	addChild(_map);
	_map->setPositionY(Winsize.height - _map->getContentSize().height);
	//下方控件
	add_ctl();
	//加载地图元素
	add_objGroup();
	//如果是Win32开启键盘监控
#ifdef WIN32
	schedule(SEL_SCHEDULE(&Game_Layer::keyboard_monitor));
#endif

	//开启mario行走监视器器
	schedule(SEL_SCHEDULE(&Game_Layer::mario_move_schedule_callback));
	//开启重力检测监视器
	schedule(SEL_SCHEDULE(&Game_Layer::gravitation_schedule_callback));
	//mario输赢监视器
	schedule(SEL_SCHEDULE(&Game_Layer::mario_WIN_AND_LOST_schedule_callback));
	//实时显示金币的监视器
	schedule(SEL_SCHEDULE(&Game_Layer::coin_visible_schedule_callback));

	SimpleAudioEngine::getInstance()->playBackgroundMusic("Sounds/OnLand.wma");

	return true;
}


void Game_Layer::coin_visible_schedule_callback(float t)
{
	_coin_count->setString(Common::format("", _mario->_coin_count, ""));
}

void Game_Layer::mario_WIN_AND_LOST_schedule_callback(float t)
{
	if (!_mario->getnow_Frame_boundingbox_onmap().intersectsRect(_mario->getmapboundingbox()))
	{
		_mario->_is_died = true;
	}
	if (_mario->_is_died)
	{
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		unschedule(SEL_SCHEDULE(&Game_Layer::mario_WIN_AND_LOST_schedule_callback));
		scheduleOnce(SEL_SCHEDULE(&Game_Layer::replace_Scene_schedule), 3);
		SimpleAudioEngine::getInstance()->playEffect("Sounds/DiaoRuXianJingSi.ogg");
	}
	else if (_mario->_touch_Flagpole)
	{
		schedule(SEL_SCHEDULE(&Game_Layer::action1));
		//关闭menu的使用
		_menuctl->setEnabled(false);
		unschedule(SEL_SCHEDULE(&Game_Layer::mario_WIN_AND_LOST_schedule_callback));
#ifdef WIN32
		unschedule(SEL_SCHEDULE(&Game_Layer::keyboard_monitor));
#endif
	}
}

void Game_Layer::action1(float t)
{
	if (_mario->standing_on_something())
	{
		int time = 2;
		_flag->runAction(MoveBy::create(time, Vec2(0, -8 * _map->getTileSize().height)));
		scheduleOnce(SEL_SCHEDULE(&Game_Layer::action2), time + 0.5);
		schedule(SEL_SCHEDULE(&Game_Layer::touch_finalpoint));

		unschedule(SEL_SCHEDULE(&Game_Layer::action1));
	}
}

void Game_Layer::action2(float t)
{
	_mario->run_automove();
}

void Game_Layer::touch_finalpoint(float t)
{
	if (_mario->getBoundingBox().intersectsRect(_finalpoint->getBoundingBox()))
	{
		_mario->stop_automove();
		scheduleOnce(SEL_SCHEDULE(&Game_Layer::goto_next_Ground), 0.5f);
		unschedule(SEL_SCHEDULE(&Game_Layer::touch_finalpoint));
	}
}

void Game_Layer::goto_next_Ground(float t)
{
	_mario->_touch_Flagpole = false;
	Scene * scene = Common::createscene(Game_Layer::create(_idx+1,_mario));
	Director::getInstance()->replaceScene(scene);
}

void Game_Layer::replace_Scene_schedule(float t)
{
	Scene * scene = Common::createscene(Grounds_Select_Layer::create());
	Director::getInstance()->replaceScene(scene);
}

#ifdef WIN32
void Game_Layer::keyboard_monitor(float t)
{
	if (GetKeyState('A') < 0)
	{
		move_left_menu_callback(NULL);
	}
	if (GetKeyState('D') < 0)
	{
		move_right_menu_callback(NULL);
	}
	if (GetKeyState('K') < 0)
	{
		jump_menu_callback(NULL);
	}
}
#endif


void Game_Layer::gravitation_schedule_callback(float t)
{
	for (int i = 0; i < _gravitation_vec.size(); i++)
	{
		Organism * organism = _gravitation_vec.at(i);
		if (!organism->standing_on_something())
		{
			if (organism->_jump_speed > 0)
			{
				organism->_jump_speed -= _gravity * t + _air_resistance * organism->_jump_speed;
				if (organism->_jump_speed < 0)
				{
					organism->_jump_speed = 0;
				}
			}
			else
			{
				organism->_down_speed += _gravity * t - _air_resistance * organism->_down_speed;
			}
		}
		else
		{
			if (organism->_down_speed != 0)
			{
				organism->_is_jump = false;
				organism->_down_speed = 0;
				organism->jump_autoadjust();
			}	
		}
	}
}

void Game_Layer::add_objGroup()
{
	TMXObjectGroup* objGroup = _map->getObjectGroup("objects");
	std::vector<Value> obj_vec = objGroup->getObjects();
	Value objPointMap;
	
	for (int i = 0; i < obj_vec.size(); i++)
	{
		objPointMap = obj_vec.at(i);
		ValueMap objPoint = objPointMap.asValueMap();
		float x = objPoint.at("x").asFloat();
		float y = objPoint.at("y").asFloat();
		std::string type = objPoint.at("type").asString();
		if (strcmp(type.c_str(), "BirthPoint") == 0)
		{
			// 创建mario
			if (_mario == NULL)
			{
				_mario = Mario_Player::create();
			}
			else
			{
				_mario->removeFromParent();
				_mario->run_monitor_switch();
				_mario->_monitor_work = false;
			}
			_map->addChild(_mario);
			_mario->birth(Vec2(x, y - _map->getTileSize().height));
		}
		else if (strcmp(type.c_str(), "mushroom") == 0)
		{
			// 创建mushroom

			Mushroom * mushroom = Mushroom::create();
			_map->addChild(mushroom);
			mushroom->birth(Vec2(x, y - _map->getTileSize().height));
		}
		else if (strcmp(type.c_str(), "tortoise") == 0)
		{
			// 创建tortoise
			Tortoise * tortoise = Tortoise::create();
			_map->addChild(tortoise);
			tortoise->birth(Vec2(x, y - _map->getTileSize().height));
		}
		else if (strcmp(type.c_str(), "flower") == 0)
		{
			// 创建flower
			Flower * flower = Flower::create();
			_map->addChild(flower);
			flower->birth(Vec2(x - _map->getTileSize().height * 0.5, y - _map->getTileSize().height));
		}
		else if (strcmp(type.c_str(), "flagpoint") == 0)
		{
			// 创建flagpoint
			_flag = Sprite::create("Object/flag.png");
			_flag->setPosition(x - _map->getTileSize().width, y - _map->getTileSize().height);
			_flag->setAnchorPoint(Vec2(0, 0));
			_flag->setLocalZOrder(100);
			_map->addChild(_flag);
		}
		else if (strcmp(type.c_str(), "finalpoint") == 0)
		{
			// 创建finalpoint
			_finalpoint = Sprite::create();
			_finalpoint->setContentSize(_map->getTileSize());
			_finalpoint->setPosition(x - _map->getTileSize().width*0.5, y - _map->getTileSize().height);
			_finalpoint->setAnchorPoint(Vec2(0, 0));
			_finalpoint->setLocalZOrder(100);
			_map->addChild(_finalpoint);
		}
		else if (strcmp(type.c_str(), "MushroomReward") == 0)
		{
			// 创建MushroomReward
			Mushroom_Reward * mushroom_reward = Mushroom_Reward::create();
			_map->addChild(mushroom_reward);
			mushroom_reward->birth(Vec2(x, y - _map->getTileSize().height));
		}
		else if (strcmp(type.c_str(), "ladderLR") == 0)
		{
			// 创建Ladder_Sprite
			LadderLR_Sprite * ladder = LadderLR_Sprite::create();
			_map->addChild(ladder);
			ladder->birth(Vec2(x, y - _map->getTileSize().height));
		}
		else if (strcmp(type.c_str(), "ladderUD") == 0)
		{
			// 创建Ladder_Sprite
			LadderUD_Sprite * ladder = LadderUD_Sprite::create();
			_map->addChild(ladder);
			ladder->birth(Vec2(x, y - _map->getTileSize().height));

		}
		else if (strcmp(type.c_str(), "flyfish") == 0)
		{
			// 创建flyfish
			FlyFish * flyfish = FlyFish::create();
			_map->addChild(flyfish);
			flyfish->birth(Vec2(x, y));
		}
		else if (strcmp(type.c_str(), "boss") == 0)
		{
			// 创建boss
			Boss * boss = Boss::create();
			_map->addChild(boss);
			boss->birth(Vec2(x, y));
		}
	}
}

void Game_Layer::add_ctl()
{
	Sprite * control_background = Sprite::create("UI/controlUI.png");
	addChild(control_background);
	control_background->setPosition(0, 0);
	control_background->setAnchorPoint(Vec2(0, 0));

	_dir_control = Sprite::create("UI/backKeyImage.png");
	_dir_control->setPosition(70, 50);
	addChild(_dir_control);

	Sprite * left = Sprite::create();
	left->setContentSize(Size(_dir_control->getContentSize().width / 2, _dir_control->getContentSize().height));
	MenuItem * left_item = MenuItemSprite::create(left, left, CC_CALLBACK_1(Game_Layer::move_left_menu_callback, this));

	Sprite * right = Sprite::create();
	right->setContentSize(Size(_dir_control->getContentSize().width / 2, _dir_control->getContentSize().height));
	MenuItem * ritht_item = MenuItemSprite::create(right, right, CC_CALLBACK_1(Game_Layer::move_right_menu_callback, this));

	MenuItem * jump_item = MenuItemImage::create("UI/AB_normal.png", "UI/AB_select.png", CC_CALLBACK_1(Game_Layer::jump_menu_callback,this));

	_menuctl = MenuCtl::create();
	_menuctl->addChild(left_item);
	_menuctl->addChild(ritht_item);
	addChild(_menuctl);

	MenuCtl * jump_menu = MenuCtl::create();
	jump_menu->addChild(jump_item);
	addChild(jump_menu);

	left_item->setPosition(70 - Winsize.width / 2, 50 - Winsize.height / 2);
	ritht_item->setPosition(70 - Winsize.width / 2, 50 - Winsize.height / 2);
	jump_item->setPosition(70 - Winsize.width / 2, 50 - Winsize.height / 2);
	Common::MoveNode(left_item, Vec2(-_dir_control->getContentSize().width / 4, 0));
	Common::MoveNode(ritht_item, Vec2(_dir_control->getContentSize().width / 4, 0));
	Common::MoveNode(jump_item, Vec2(Winsize.width - 198,-15));

	_coin_count = LabelAtlas::create("0", "fonts/fps_images.png", 12, 32, '.');
	_coin_count->setPosition(Winsize.width / 2 , Winsize.height - _coin_count->getContentSize().height);
	_coin_count->setAnchorPoint(Vec2(0, 0.5));
	addChild(_coin_count);

	Texture2D* texture = Director::getInstance()->getTextureCache()->addImage("Object/blinkcoin.png");

	SpriteFrame* frame = SpriteFrame::createWithTexture(texture, Rect(0, 0, texture->getContentSize().width / 3,
		texture->getContentSize().height/3));
	Sprite * coin = Sprite::createWithSpriteFrame(frame);
	addChild(coin);
	coin->setAnchorPoint(Vec2(1, 0.5));
	coin->setPosition(_coin_count->getPosition().x - 10, _coin_count->getPosition().y- coin->getContentSize().height*0.5);
}

void Game_Layer::mario_move_schedule_callback(float t)
{
	if(_mario->_left_speed == 0&& _mario->_right_speed == 0)
	{
		Texture2D* texture = Director::getInstance()->getTextureCache()->addImage("UI/backKeyImage.png");
		_dir_control->setTexture(texture);
		if (_mario->_face_dir == Common::Face_dir::Right)
		{
			if (_mario->_iseatMushroom)
			{
				_mario->setDisplayFrameWithAnimationName("red_Big_mario_move_right", 0);
			}
			else
			{
				_mario->setDisplayFrameWithAnimationName("red_small_mario_move_right", 0);
			}
		}
		else if (_mario->_face_dir == Common::Face_dir::Left)
		{
			if (_mario->_iseatMushroom)
			{
				_mario->setDisplayFrameWithAnimationName("red_Big_mario_move_left", 0);
			}
			else
			{
				_mario->setDisplayFrameWithAnimationName("red_small_mario_move_left", 0);
			}
		}
		_mario->_is_moving_left = false;
		_mario->_is_moving_right = false;
	}
	//监视mario使其在屏幕中
	Vec2 mario_world_position = _mario->getParent()->convertToWorldSpace(_mario->getPosition());
	float map_left_positionX = _map->getParent()->convertToWorldSpace(_map->getPosition()).x;
	float map_ritht_positionX = map_left_positionX + _map->getContentSize().width;
	//如果mario位置超过地图一半且地图最右侧仍在屏幕外面
	int move_long = mario_world_position.x - Winsize.width*0.5;
	if (mario_world_position.x > Winsize.width*0.5&&map_ritht_positionX > Winsize.width)
	{
		if (move_long>map_ritht_positionX - Winsize.width)
		{
			Common::MoveNode(_map, Vec2(Winsize.width - map_ritht_positionX, 0));
		}
		else
		{
			Common::MoveNode(_map, Vec2(-move_long, 0));
		}
	}
	else if (mario_world_position.x < Winsize.width*0.5&&map_left_positionX <0)
	{
		if (move_long<  map_left_positionX)
		{
			Common::MoveNode(_map, Vec2(- map_left_positionX, 0));
		}
		else
		{
			Common::MoveNode(_map, Vec2(-move_long, 0));
		}
	}
	
}

void Game_Layer::jump_menu_callback(Ref * ref)
{
	if (_mario->standing_on_something())
	{
		SimpleAudioEngine::getInstance()->playEffect("Sounds/Jump.ogg");
		_mario->_jump_speed = _mario->_jump_power;
	}
}

void Game_Layer::move_left_menu_callback(Ref * ref)
{
	Texture2D* texture = Director::getInstance()->getTextureCache()->addImage("UI/backKeyLeft.png");
	_dir_control->setTexture(texture);
	_mario->moveleft_ctl();
}

void Game_Layer::move_right_menu_callback(Ref * ref)
{
	Texture2D* texture = Director::getInstance()->getTextureCache()->addImage("UI/backKeyRight.png");
	_dir_control->setTexture(texture);
	_mario->moveright_ctl();
}

Game_Layer * Game_Layer::create(int idx, Mario_Player * mario)
{
	Game_Layer * pRet = new Game_Layer;
	if (pRet&&pRet->init(idx,mario))
	{
		pRet->autorelease();
	}
	else
	{
		delete pRet;
		pRet = NULL;
	}
	return pRet;
}