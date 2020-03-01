#include "Game_Layer.h"
#include "Tank_Friends.h"
#include "MenuCtl.h"
#include "Bullet_Friend.h"
#include "Tank_Enemy.h"
#include "Bullet_Enemy.h"
#include "Start_Layer.h"
#include "Tank_Item.h"
#include "Setup_Layer.h"
#include "Rinkint_List_Layer.h"

bool Game_Layer::init(int index, Tank_Friends* tank_friend1, Tank_Friends * tank_friend2)
{
	if (!LayerColor::initWithColor(Color4B(125,125,125,255)))
	{
		return false;
	}
	SimpleAudioEngine::getInstance()->playEffect("sounds/levelstarting.wav");
	srand(time(NULL));

	_tank_friend1 = tank_friend1;
	_tank_friend2 = tank_friend2;

	_index = index;
	_map = TMXTiledMap::create(Common::format("Rounds/Round", index + 1, ".tmx"));
	
	_map->setAnchorPoint(Vec2(0.5, 0.5));
	_map->setPosition(Winsize.width*0.5, Winsize.height*0.5);
	_map->setContentSize(Size(Winsize.height, Winsize.height));
	
	

	//设计结束
	DrawNode * node = DrawNode::create();
	node->drawSolidRect(Vec2(Winsize.width*0.5-Winsize.height*0.5, 0),
		Vec2(Vec2(Winsize.width*0.5 + Winsize.height*0.5, Winsize.height)), Color4F(0, 0, 0, 1));
	addChild(node);
	
	addChild(_map);
	
	if (!_tank_friend1)
	{
		_tank_friend1 = Tank_Friends::create();
		_map->addChild(_tank_friend1);
	}
	else
	{
		_tank_friend1->retain();
		_tank_friend1->removeFromParent();
		_map->addChild(_tank_friend1);
		_tank_friend1->release();
		_tank_friend1->_can_shoot = true;
		_tank_friend1->_safe_top = false;
	}
	
	_tank_friend1->set_picture("tank/player/player1U.png");
	_tank_friend1->setContentSize(Size(Winsize.height/13-6.1,Winsize.height/13-6.1));
	set_onmap_position(_tank_friend1, Vec2(10, 25));

	
	MenuItem * item1 = MenuItemImage::create("paddle/top.png", "paddle/top_press.png", CC_CALLBACK_1(Game_Layer::dir_menu_callback, this));
	MenuItem * item2 = MenuItemImage::create("paddle/buttom.png", "paddle/buttom_press.png", CC_CALLBACK_1(Game_Layer::dir_menu_callback, this));
	MenuItem * item3 = MenuItemImage::create("paddle/left.png", "paddle/left_press.png", CC_CALLBACK_1(Game_Layer::dir_menu_callback, this));
	MenuItem * item4 = MenuItemImage::create("paddle/right.png", "paddle/right_press.png", CC_CALLBACK_1(Game_Layer::dir_menu_callback, this));
	item1->setTag(Common::Dir_Control::Up);
	item2->setTag(Common::Dir_Control::Down);
	item3->setTag(Common::Dir_Control::Left);
	item4->setTag(Common::Dir_Control::Right);
	MenuCtl * menuctl = MenuCtl::create();
	menuctl->addChild(item1);
	menuctl->addChild(item2);
	menuctl->addChild(item3);
	menuctl->addChild(item4);
	addChild(menuctl);
	Vec2 dirctl_origin_place = Vec2(-Winsize.width*0.35, -Winsize.height*0.2);
	float dist = 60;
	item1->setPosition(dirctl_origin_place.x , dirctl_origin_place.y+ dist);
	item2->setPosition(dirctl_origin_place.x , dirctl_origin_place.y- dist);
	item3->setPosition(dirctl_origin_place.x - dist, dirctl_origin_place.y);
	item4->setPosition(dirctl_origin_place.x + dist, dirctl_origin_place.y );

	MenuItem * item = MenuItemImage::create("paddle/fire.png","paddle/fire_press.png",CC_CALLBACK_1(Game_Layer::shoot_menu_callback,this));
	item->setPosition(Winsize.width*0.3, -Winsize.height*0.2);
	Menu * shoot_menu = Menu::create(item, NULL);
	addChild(shoot_menu);

	MenuItem * setup_item = MenuItemImage::create("paddle/pause.png", "paddle/pause_press.png", CC_CALLBACK_1(Game_Layer::setup_menu_callback, this));
	setup_item->setPosition(Winsize.width*0.75 - _map->getTileSize().width*_map->getMapSize().width*0.5, Winsize.height*0.4);
	setup_item->setAnchorPoint(Vec2(0.5, 0.5));
	Menu * setup_menu = Menu::create(setup_item, NULL); 
	
	addChild(setup_menu);

	//开启友军子弹检测
	schedule(SEL_SCHEDULE(&Game_Layer::bullet_friend_collision_detection));

	//自动添加敌军坦克的定时器
	schedule(SEL_SCHEDULE(&Game_Layer::add_enemy_tank_callback),3);

	//敌方坦克行走的定时器
	schedule(SEL_SCHEDULE(&Game_Layer::enemy_move_callback));

	//敌方坦克射击的定时器
	schedule(SEL_SCHEDULE(&Game_Layer::enemy_shoot_callback), 1);

	//开启敌方子弹检测
	schedule(SEL_SCHEDULE(&Game_Layer::bullet_enemy_collision_detection));

	//加载敌方坦克爆炸帧动画
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("boom/blast.plist");
	Vector<SpriteFrame *> frame_vec;
	for (int i = 1; i <= 8; ++i)
	{
		const char* spriteFrameName = Common::format("blast", i , ".gif");
		SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName);
		frame_vec.pushBack(frame);
	}
	Animation * animation = Animation::createWithSpriteFrames(frame_vec);
	animation->setDelayPerUnit(0.05f);
	AnimationCache::getInstance()->addAnimation(animation, "enemy_boom");

	//设置界面右边的坦克属性可视化以及得分
	_tank_friend_life_label = Label::createWithTTF(Common::format("", _tank_friend1->_life), "fonts/arial.ttf", 30);
	_tank_friend_life_label->setColor(Color3B::BLACK);
	_tank_friend_life_label->setAnchorPoint(Vec2(0.5, 0.5));
	_tank_friend_life_label->setPosition(Winsize.width*0.95, Winsize.height*0.2);
	addChild(_tank_friend_life_label);
	Sprite * tank_spr = Sprite::create("tank/player/player1U.png");
	tank_spr->setPosition(Winsize.width*0.9, Winsize.height*0.2);
	tank_spr->setContentSize(Size(30, 30));
	tank_spr->setAnchorPoint(Vec2(0.5, 0.5));
	addChild(tank_spr);

	_tank_friend_file_power_label = Label::createWithTTF(Common::format("", _tank_friend1->_file_power), "fonts/arial.ttf", 30);
	_tank_friend_file_power_label->setColor(Color3B::BLACK);
	_tank_friend_file_power_label->setAnchorPoint(Vec2(0.5, 0.5));
	_tank_friend_file_power_label->setPosition(Winsize.width*0.95, Winsize.height*0.2-50);
	addChild(_tank_friend_file_power_label);
	Sprite * bullet_spr = Sprite::create("tank/bullet.png");
	bullet_spr->setPosition(Winsize.width*0.9, Winsize.height*0.2-50);
	bullet_spr->setContentSize(Size(30, 30));
	bullet_spr->setAnchorPoint(Vec2(0.5, 0.5));
	addChild(bullet_spr);

	_score_label = Label::createWithTTF(Common::format("", _tank_friend1->_score), "fonts/arial.ttf", 30);
	_score_label->setColor(Color3B::BLACK);
	_score_label->setAnchorPoint(Vec2(0.5, 0.5));
	_score_label->setPosition(Winsize.width*0.75 + _map->getTileSize().width*_map->getMapSize().width*0.25, Winsize.height*0.6);
	addChild(_score_label);
	Sprite * score_spr = Sprite::create("scoreboard/score.png");
	score_spr->setPosition(Winsize.width*0.75+_map->getTileSize().width*_map->getMapSize().width*0.25, Winsize.height*0.7);
	score_spr->setAnchorPoint(Vec2(0.5, 0.5));
	addChild(score_spr);

	Label * remain_enemy = Label::createWithTTF("enemy", "fonts/arial.ttf", 30);
	remain_enemy->setColor(Color3B::BLACK);
	remain_enemy->setAnchorPoint(Vec2(0.5, 0.5));
	remain_enemy->setPosition(Winsize.width*0.75 + _map->getTileSize().width*_map->getMapSize().width*0.25, Winsize.height*0.6-50);
	addChild(remain_enemy);
	_remain_enemy_label = Label::createWithTTF(Common::format("", _remain_enemy), "fonts/arial.ttf", 30);
	_remain_enemy_label->setColor(Color3B::BLACK);
	_remain_enemy_label->setAnchorPoint(Vec2(0.5, 0.5));
	_remain_enemy_label->setPosition(Winsize.width*0.75 + _map->getTileSize().width*_map->getMapSize().width*0.25, Winsize.height*0.6-100);
	addChild(_remain_enemy_label);


	//开启友方坦克死亡监控以及通过本关监控
	schedule(SEL_SCHEDULE(&Game_Layer::win_and_lost_callfunc),5);

	//开启友方坦克获得道具检测
	schedule(SEL_SCHEDULE(&Game_Layer::eat_item_callfunc));

	return true;
}



void Game_Layer::setup_menu_callback(Ref * ref)
{
	Setup_Layer * layer = Setup_Layer::create();
	Director::getInstance()->pause();
	addChild(layer);
}

void Game_Layer::eat_item_callfunc(float t)
{
#ifdef WIN32
	if (GetKeyState('A') < 0)
	{
		if (_tank_friend1->_dir != Common::Dir_Control::Left)
		{
			_tank_friend1->turn(Common::Dir_Control::Left);
		}
		_tank_friend1->move();
	}
	else if (GetKeyState('S') < 0)
	{
		if (_tank_friend1->_dir != Common::Dir_Control::Down)
		{
			_tank_friend1->turn(Common::Dir_Control::Down);
		}
		_tank_friend1->move();
	}
	else if (GetKeyState('D') < 0)
	{
		if (_tank_friend1->_dir != Common::Dir_Control::Right)
		{
			_tank_friend1->turn(Common::Dir_Control::Right);
		}
		_tank_friend1->move();
	}
	else if (GetKeyState('W') < 0)
	{
		if (_tank_friend1->_dir != Common::Dir_Control::Up)
		{
			_tank_friend1->turn(Common::Dir_Control::Up);
		}
		_tank_friend1->move();
	}
	else if (GetKeyState('J') < 0)
	{
		if (_tank_friend1->_can_shoot)
		{
			Bullet_Friend * bullet = _tank_friend1->shoot();
			_map->addChild(bullet);
			_bullet_friend_vec.pushBack(bullet);
		}
	}
#endif
	for (int i = 0; i < _tank_item_vec.size(); i++)
	{
		Tank_Item * item = _tank_item_vec.at(i);
		if (item->getBoundingBox().intersectsRect(_tank_friend1->getBoundingBox()))
		{
			if (item->_type == Common::Item_Type::active)
			{
				_tank_friend1->_life++;
				_tank_friend1->injured(10);
				_tank_friend_life_label->setString(Common::format("", _tank_friend1->_life));
				SimpleAudioEngine::getInstance()->playEffect("sounds/pause.wav");
			}
			else if (item->_type == Common::Item_Type::bomb)
			{
				SimpleAudioEngine::getInstance()->playEffect("sounds/pause.wav");
				for (int count = _tank_enemy_vec.size() - 1; count >= 0; count--)
				{

					Tank_Enemy * enemy_tank = _tank_enemy_vec.at(count);
					int score = enemy_tank->get_score();
					_tank_friend1->_score += score;
					_score_label->setString(Common::format("", _tank_friend1->_score));

					//如果打中的敌方坦克是红色的
					if (enemy_tank->_type == Common::Enemy_Tank_Type::Red_normal_tank || enemy_tank->_type == Common::Enemy_Tank_Type::Red_speed_tank || (enemy_tank->_type == Common::Enemy_Tank_Type::Red_panzer&&enemy_tank->_life == 3))
					{
						int item_type = rand() % 6;
						
						Tank_Item * item = Tank_Item::create((Common::Item_Type)item_type);
						item->setAnchorPoint(Vec2(0.5, 0.5));
						item->setPosition(CCRANDOM_0_1()*_map->getTileSize().width*_map->getMapSize().width, CCRANDOM_0_1()*_map->getTileSize().height*_map->getMapSize().height);
						_map->addChild(item);
						_tank_item_vec.pushBack(item);
					}
					enemy_tank->_life = 1;
					enemy_tank->injured();
					if (enemy_tank->_life == 0)
					{
						Animate * animate = Animate::create(AnimationCache::getInstance()->getAnimation("enemy_boom"));
						CallFunc * callfunc1 = CallFunc::create(CC_CALLBACK_0(Game_Layer::delete_enemy, this, enemy_tank));
						Sequence * seq = Sequence::createWithTwoActions(animate, callfunc1);
						enemy_tank->runAction(seq);
						
						SimpleAudioEngine::getInstance()->playEffect("sounds/eexplosion.wav"); 
					}
					_tank_enemy_vec.erase(count);
				}
			}
			else if (item->_type == Common::Item_Type::mintank)
			{
				SimpleAudioEngine::getInstance()->playEffect("sounds/pause.wav");
				_tank_friend1->_life++;
				_tank_friend_life_label->setString(Common::format("", _tank_friend1->_life));
			}
			else if (item->_type == Common::Item_Type::star)
			{
				SimpleAudioEngine::getInstance()->playEffect("sounds/pause.wav");
				if (_tank_friend1->_file_power >= 3)
				{
					_tank_friend1->_score += 1000;
					_score_label->setString(Common::format("", _tank_friend1->_score));
				}
				else
				{
					_tank_friend1->_file_power++;
					_tank_friend_file_power_label->setString(Common::format("", _tank_friend1->_file_power));
				}	
			}
			else if (item->_type == Common::Item_Type::steel)
			{
				SimpleAudioEngine::getInstance()->playEffect("sounds/pause.wav");
				Vec2 place[8]; 
				place[0] = Vec2(11, 25);
				place[1] = Vec2(11, 24);
				place[2] = Vec2(11, 23);
				place[3] = Vec2(12, 23);
				place[4] = Vec2(13, 23);
				place[5] = Vec2(14, 23);
				place[6] = Vec2(14, 24);
				place[7] = Vec2(14, 25);
				TMXLayer* layer = _map->getLayer("layer_0");
				for (int j = 0; j < 8; j++)
				{
					layer->setTileGID(5, place[j]);
					scheduleOnce(SEL_SCHEDULE(&Game_Layer::set_block), 10);
				}
			}
			else if (item->_type == Common::Item_Type::timer)
			{
				SimpleAudioEngine::getInstance()->playEffect("sounds/pause.wav");
				unschedule(SEL_SCHEDULE(&Game_Layer::enemy_move_callback));
				unschedule(SEL_SCHEDULE(&Game_Layer::enemy_shoot_callback));
				scheduleOnce(SEL_SCHEDULE(&Game_Layer::timer_resume_callback), 10);
				
			}
			item->removeFromParent();
			_tank_item_vec.erase(i);
			
		}
	}
}

void Game_Layer::timer_resume_callback(float t)
{
	//敌方坦克行走的定时器
	schedule(SEL_SCHEDULE(&Game_Layer::enemy_move_callback));

	//敌方坦克射击的定时器
	schedule(SEL_SCHEDULE(&Game_Layer::enemy_shoot_callback), 1);
}

void Game_Layer::set_block(float t)
{
	Vec2 place[8];
	place[0] = Vec2(11, 25);
	place[1] = Vec2(11, 24);
	place[2] = Vec2(11, 23);
	place[3] = Vec2(12, 23);
	place[4] = Vec2(13, 23);
	place[5] = Vec2(14, 23);
	place[6] = Vec2(14, 24);
	place[7] = Vec2(14, 25);
	TMXLayer* layer = _map->getLayer("layer_0");
	for (int j = 0; j < 8; j++)
	{
		layer->setTileGID(13, place[j]);
	}
}

void Game_Layer::win_and_lost_callfunc(float t)
{
	if (_tank_friend1->_life <= 0)
	{
		lost();
	}
	else if (_remain_enemy <= 0 && _tank_enemy_vec.size() == 0)
	{
		int index = _index + 1;
		if (index >= 20)
		{
			index = 0;
		}
		Game_Layer * layer = Game_Layer::create(index, _tank_friend1, _tank_friend2);
		Scene * scene = Common::createscene(layer);
		Director::getInstance()->replaceScene(scene);
	}
}

void Game_Layer::lost()
{
	Layer * layer = Layer::create();
	layer->setPosition(0, 0);
	layer->setAnchorPoint(Vec2(0.5, 0.5));
	addChild(layer);
	Director::getInstance()->pause();
	MenuItem * item = MenuItemImage::create("start_source/over.png", "start_source/over.png", CC_CALLBACK_1(Game_Layer::lost_menu_callfunc, this));
	item->setPosition(0, 0);
	item->setAnchorPoint(Vec2(0.5, 0.5));
	Menu * menu = Menu::create(item, NULL);
	SimpleAudioEngine::getInstance()->playEffect("sounds/gameover.wav");

	EventListenerTouchOneByOne * mylistener = EventListenerTouchOneByOne::create();
	mylistener->onTouchBegan = [=](Touch* touch, Event* event) mutable//指按下时
	{
		return true;
	};

	mylistener->onTouchMoved = [=](Touch* touch, Event* event) mutable//指移动时
	{
	};
	mylistener->onTouchEnded = [=](Touch* touch, Event* event) //松开时
	{
	};
	mylistener->setSwallowTouches(true);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(mylistener, layer);

	layer->addChild(menu);
}

void Game_Layer::lost_menu_callfunc(Ref * ref)
{
	Director::getInstance()->resume();
	Rinkint_List_Layer * layer = Rinkint_List_Layer::create(_tank_friend1->_score);
	Scene * scene = Common::createscene(layer);
	Director::getInstance()->replaceScene(scene);
}

void Game_Layer::bullet_enemy_collision_detection(float t)
{
	
	Vec2 position;
	Vec2 rect_position[4];
	for (int i = _bullet_enemy_vec.size() - 1; i >= 0; i--)
	{
		bool flag1 = false;
		Bullet_Enemy * bullet = _bullet_enemy_vec.at(i);
		rect_position[0] = Vec2(bullet->getBoundingBox().getMinX() + 1, bullet->getBoundingBox().getMinY() + 1);
		rect_position[1] = Vec2(bullet->getBoundingBox().getMinX() + 1, bullet->getBoundingBox().getMaxY() - 1);
		rect_position[2] = Vec2(bullet->getBoundingBox().getMaxX() - 1, bullet->getBoundingBox().getMinY() + 1);
		rect_position[3] = Vec2(bullet->getBoundingBox().getMaxX() - 1, bullet->getBoundingBox().getMaxY() - 1);
		for (int j = 0; j < 4; j++)
		{
			Vec2 map_point = convert_to_map(rect_position[j]);
			if (map_point.x < 0 || map_point.x >= _map->getMapSize().width || map_point.y < 0 || map_point.y >= _map->getMapSize().height)//如果已经在地图外面
			{
				_bullet_enemy_vec.erase(i);
				bullet->removeFromParent();

				break;
			}

			TMXLayer* layer = _map->getLayer("layer_0");
			int gid = layer->getTileGIDAt(map_point);
			Common::TileType tt = Common::getTileType(gid);
			if (tt == Common::TileType::BLOCK)//撞到砖块
			{
				_bullet_enemy_vec.erase(i);
				bullet->removeFromParent();
				layer->setTileGID(0, map_point);
				break;
			}
			if (tt == Common::TileType::STEEL)//撞到钢板
			{
				_bullet_enemy_vec.erase(i);
				bullet->removeFromParent();
				break;
			}
			if (tt == Common::TileType::HOME)//打到家
			{
				_bullet_enemy_vec.erase(i);
				bullet->removeFromParent();
				lost();
				flag1 = true;
				break;
			}
			if (_tank_friend1->getBoundingBox().containsPoint(rect_position[j])&&_tank_friend1->_safe_top==false)//撞到友方坦克
			{
				_bullet_enemy_vec.erase(i);
				bullet->removeFromParent();
				_tank_friend1->injured(2);
				_tank_friend_life_label->setString(Common::format("", _tank_friend1->_life));
				break;
			}
		}
		if (flag1 == true)
		{
			break;
		}
	}
}

void Game_Layer::enemy_shoot_callback(float t)
{
	for (int i = 0; i < _tank_enemy_vec.size(); i++)
	{
		Bullet_Enemy * bullet = _tank_enemy_vec.at(i)->shoot();
		_map->addChild(bullet);
		_bullet_enemy_vec.pushBack(bullet);
	}
}

void Game_Layer::enemy_move_callback(float t)
{
	for (int i = 0; i < _tank_enemy_vec.size(); i++)
	{
		if (!_tank_enemy_vec.at(i)->canmove())
		{
			_tank_enemy_vec.at(i)->turn((Common::Dir_Control)(rand() % 4));
		}
		else
		{
			_tank_enemy_vec.at(i)->move();
		}
		
	}
}

void Game_Layer::add_enemy_tank_callback(float t)
{
	if (_remain_enemy <= 0)
	{
		return;
	}
	Vec2 map_point;
	if (_num == 0)
	{
		map_point.x = 1;
		map_point.y = 1;
	}
	else if (_num == 1)
	{
		map_point.x = 13;
		map_point.y = 1;
	}
	else if (_num == 2)
	{
		map_point.x = 25;
		map_point.y = 1;
	}
	_num++;
	if (_num > 2)
	{
		_num = 0;
	}
	Vec2 position = convert_to_point(map_point);
	int type_id = rand()%12;
	if (type_id == 0)
	{
		type_id = 0;
	}
	else if (type_id == 1 || type_id == 2 || type_id == 3)
	{
		type_id = 1;
	}
	else if (type_id == 4)
	{
		type_id = 2;
	}
	else if (type_id == 5 || type_id == 6 || type_id == 7)
	{
		type_id = 3;
	}
	else if (type_id == 8)
	{
		type_id = 4;
	}
	else if (type_id == 9 || type_id == 10 || type_id == 11)
	{
		type_id = 5;
	}

	 Tank_Enemy  *	enemy = Tank_Enemy::create(Common::Enemy_Tank_Type(type_id));
	
	_map->addChild(enemy);
	enemy->setPosition(position);
	enemy->setContentSize(Size(_map->getTileSize().width*2, _map->getTileSize().height*2));
	enemy->turn((Common::Dir_Control)(rand()%4));
	_tank_enemy_vec.pushBack(enemy);
	_remain_enemy--;
	_remain_enemy_label->setString(Common::format("", _remain_enemy));
}

//友方子弹检测
void Game_Layer::bullet_friend_collision_detection(float t)
{
	Vec2 position;
	Vec2 rect_position[4];
	for (int i = _bullet_friend_vec.size() - 1; i >= 0; i--)
	{
		
		Bullet_Friend * bullet = _bullet_friend_vec.at(i);
		rect_position[0] = Vec2(bullet->getBoundingBox().getMinX()+1, bullet->getBoundingBox().getMinY() +1);
		rect_position[1] = Vec2(bullet->getBoundingBox().getMinX() +1, bullet->getBoundingBox().getMaxY() -1);
		rect_position[2] = Vec2(bullet->getBoundingBox().getMaxX() -1, bullet->getBoundingBox().getMinY() +1);
		rect_position[3] = Vec2(bullet->getBoundingBox().getMaxX() -1, bullet->getBoundingBox().getMaxY() -1);
		
		bool flag1 = false;
		//与敌方子弹相撞
		for (int j = _bullet_enemy_vec.size() - 1; j >= 0; j--)
		{
			if (_bullet_friend_vec.at(i)->getBoundingBox().intersectsRect(_bullet_enemy_vec.at(j)->getBoundingBox()))
			{
				Bullet_Enemy * enemy_bullet = _bullet_enemy_vec.at(j);
				_bullet_friend_vec.erase(i);//删除友方子弹
				bullet->removeFromParent();
				_bullet_enemy_vec.erase(j);//删除敌方子弹
				enemy_bullet->removeFromParent();
				flag1 = true;
				break;
			}
		}
		if (flag1)
		{
			continue;
		}
		
		for (int j = 0; j < 4; j++)
		{
			
			Vec2 map_point = convert_to_map(rect_position[j]);
			if (map_point.x < 0 || map_point.x >= _map->getMapSize().width || map_point.y < 0 || map_point.y >= _map->getMapSize().height)//如果已经在地图外面
			{
				_bullet_friend_vec.erase(i);
				bullet->removeFromParent();
				
				break;
			}
			
			TMXLayer* layer = _map->getLayer("layer_0");
			int gid = layer->getTileGIDAt(map_point);
			Common::TileType tt = Common::getTileType(gid);
			if (tt == Common::TileType::BLOCK)//撞到砖块
			{
				SimpleAudioEngine::getInstance()->playEffect("sounds/steelhit.wav");
				_bullet_friend_vec.erase(i);
				bullet->removeFromParent();
				layer->setTileGID(0, map_point);
				break;
			}
			if (tt == Common::TileType::STEEL)//撞到钢板
			{
				SimpleAudioEngine::getInstance()->playEffect("sounds/steelhit.wav");
				_bullet_friend_vec.erase(i);
				bullet->removeFromParent();
				if (_tank_friend1->_file_power == 3)
				{
					layer->setTileGID(0, map_point);
				}
				break;
			}

			if (tt == Common::TileType::HOME)//打到家
			{
				_bullet_friend_vec.erase(i);
				bullet->removeFromParent();
				lost();
				break;
			}

			if (tt == Common::TileType::STEEL)//
			{
				_bullet_friend_vec.erase(i);
				bullet->removeFromParent();
				if (_tank_friend1->_file_power == 3)
				{
					layer->setTileGID(0, map_point);
				}
				break;
			}
			bool flag2 = false;
			//击中敌军
			for (int count = _tank_enemy_vec.size()-1; count >= 0; count--)
			{

				Tank_Enemy * enemy_tank = _tank_enemy_vec.at(count);
				if (enemy_tank->getBoundingBox().containsPoint(rect_position[j]) && enemy_tank->_life>0)
				{
					SimpleAudioEngine::getInstance()->playEffect("sounds/steelhit.wav");
					flag2 = true;
					bullet->removeFromParent();
					_bullet_friend_vec.erase(i);
					
					//如果打中的敌方坦克是红色的
					if (enemy_tank->_type == Common::Enemy_Tank_Type::Red_normal_tank || enemy_tank->_type == Common::Enemy_Tank_Type::Red_speed_tank || (enemy_tank->_type == Common::Enemy_Tank_Type::Red_panzer&&enemy_tank->_life==3))
					{
						int item_type = rand() % 6;
						Tank_Item * item = Tank_Item::create((Common::Item_Type)item_type);
						item->setAnchorPoint(Vec2(0.5, 0.5));
						item->setPosition(CCRANDOM_0_1()*_map->getTileSize().width*_map->getMapSize().width, CCRANDOM_0_1()*_map->getTileSize().height*_map->getMapSize().height);
						_map->addChild(item);
						_tank_item_vec.pushBack(item);
					}

					enemy_tank->injured();
					if (enemy_tank->_life == 0)
					{
						SimpleAudioEngine::getInstance()->playEffect("sounds/eexplosion.wav");
						
						
						int score = enemy_tank->get_score();
						_tank_friend1->_score += score;
						_score_label->setString(Common::format("", _tank_friend1->_score));
						Animate * animate = Animate::create(AnimationCache::getInstance()->getAnimation("enemy_boom"));
						_tank_enemy_vec.erase(count);
						CallFunc * callfunc1 = CallFunc::create(CC_CALLBACK_0(Game_Layer::delete_enemy, this, enemy_tank));
						Sequence * seq = Sequence::createWithTwoActions(animate, callfunc1);
						enemy_tank->runAction(seq);
						break;
					}
				}
				if (flag2)
				{
					break;
				}
			}
			if (flag2)
			{
				break;
			}
		}
	}
}

void Game_Layer::delete_enemy(Tank_Enemy * enemy)
{	
	enemy->removeFromParent();
	
}

void Game_Layer::shoot_menu_callback(Ref * ref)
{
	if (_tank_friend1->_can_shoot)
	{
		Bullet_Friend * bullet = _tank_friend1->shoot();
		_map->addChild(bullet);
		_bullet_friend_vec.pushBack(bullet);
	}
}

void Game_Layer::dir_menu_callback(Ref * ref)
{
	Common::Dir_Control tag = (Common::Dir_Control)((MenuItem *)ref)->getTag();
	if (_tank_friend1->_dir != tag)
	{
		_tank_friend1->turn(tag);
	}
	if (_tank_friend1->canmove())
	{
		_tank_friend1->move();
	}
	
}

void Game_Layer::set_onmap_position(Node * node, Vec2 tile_point)
{
	node->setPosition(convert_to_point(tile_point));
}

Vec2 Game_Layer::convert_to_map(Vec2 position)
{
	int origin_x = 0;
	int origin_y = _map->getPosition().y +(_map->getContentSize().height - _map->getTileSize().height*_map->getMapSize().height / 2);
	
	
	Vec2 point;
	int x = (int)(position.x - origin_x) / _map->getTileSize().width;
	int y = (int)(origin_y - position.y) / _map->getTileSize().height;
	point.x = (float)x;
	point.y = (float)y;

	return point;
}

Vec2 Game_Layer::convert_to_point(Vec2 tile_point)
{
	
	float origin_x = 0;
	float origin_y = _map->getPosition().y + (_map->getContentSize().height - _map->getTileSize().height*_map->getMapSize().height / 2);
	
	Vec2 point;
	point.x =  origin_x + _map->getTileSize().width*tile_point.x;
	point.y = origin_y - tile_point.y * _map->getTileSize().height;
	
	return point;
}

Game_Layer * Game_Layer::create(int index, Tank_Friends* tank_friend1, Tank_Friends * tank_friend2)
{
	Game_Layer * pRet = new Game_Layer;
	if (pRet&&pRet->init(index, tank_friend1 ,tank_friend2))
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