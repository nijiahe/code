#include "Tank_Friends.h"
#include "Game_Layer.h"
#include "Bullet_Friend.h"


bool Tank_Friends::init()
{
	if (!Tank::init())
	{
		return false;
	}
	
	physics_init(3, 0, 2);

	return true;
}

void Tank_Friends::injured(int time)
{
	_life--;
	Sequence * seq = Sequence::createWithTwoActions(Blink::create(time, 4 * time), Show::create());
	this->runAction(seq);
	_safe_top = true;
	scheduleOnce(SEL_SCHEDULE(&Tank_Friends::safe_top_schedule), time);
}

void Tank_Friends::safe_top_schedule(float t)
{
	_safe_top = false;
}


Bullet_Friend * Tank_Friends::shoot()
{
	Bullet_Friend* bullet = Bullet_Friend::create();
	bullet->set_picture("tank/bullet.png");
	Vec2 head_point;
	int speed = 4;
	if (_dir == Common::Dir_Control::Up)
	{
		head_point.x = getPosition().x;
		head_point.y = getPosition().y+getContentSize().height*0.5;
		
		bullet->runAction(MoveBy::create(Winsize.width / 4 / 60, Vec2(0, Winsize.width)));
	}
	if (_dir == Common::Dir_Control::Down)
	{
		head_point.x = getPosition().x;
		head_point.y = getPosition().y - getContentSize().height*0.5;
		bullet->runAction(MoveBy::create(Winsize.width / 4 / 60, Vec2(0, -Winsize.width)));
	}
	if (_dir == Common::Dir_Control::Left)
	{
		head_point.x = getPosition().x- getContentSize().width*0.5;
		head_point.y = getPosition().y ;
		bullet->runAction(MoveBy::create(Winsize.width / 4 / 60, Vec2(-Winsize.width,0 )));
	}
	if (_dir == Common::Dir_Control::Right)
	{
		head_point.x = getPosition().x + getContentSize().width*0.5;
		head_point.y = getPosition().y ;
		bullet->runAction(MoveBy::create(Winsize.width / 4 / 60, Vec2(Winsize.width, 0)));
	}

	bullet->setPosition(head_point);
	_can_shoot = false;
	scheduleOnce(SEL_SCHEDULE(&Tank_Friends::shoot_schedule),(float)2/(3+_file_power));
	

	return bullet;
}

void Tank_Friends::shoot_schedule(float t)
{
	_can_shoot = true;
}

bool Tank_Friends::canmove()
{
	Game_Layer * gamelayer = (Game_Layer *)getParent()->getParent();
	TMXTiledMap * map = gamelayer->_map;
	Vec2 des_position;

	for (int i = 0; i < gamelayer->_tank_enemy_vec.size(); i++)
	{
		
		if (gamelayer->_tank_enemy_vec.at(i)->getBoundingBox().intersectsRect(this->getBoundingBox()))
		{
			return false;
		}
	}

	if (_dir == Common::Dir_Control::Up)
	{
		des_position = Vec2(getPosition().x, getPosition().y + _speed);	
	}
	if (_dir == Common::Dir_Control::Down)
	{
		des_position = Vec2(getPosition().x , getPosition().y - _speed);
	}
	if (_dir == Common::Dir_Control::Left)
	{
		des_position = Vec2(getPosition().x- _speed, getPosition().y);
	}
	if (_dir == Common::Dir_Control::Right)
	{
		des_position = Vec2(getPosition().x + _speed, getPosition().y);
	}

	Rect rect = Rect(des_position.x - getContentSize().width*0.5, des_position.y - getContentSize().height*0.5, getContentSize().width, getContentSize().height);
	Vec2 vec[4];
	vec[0] = Vec2(rect.getMinX()+0.01, rect.getMinY()+0.01);
	vec[1] = Vec2(rect.getMinX()+0.01, rect.getMaxY()-0.01);
	vec[2] = Vec2(rect.getMaxX()- 0.01, rect.getMinY()+ 0.01);
	vec[3] = Vec2(rect.getMaxX() - 0.01, rect.getMaxY() - 0.01);


	Rect map_rect = Rect(Vec2(0, Winsize.height*0.5 - map->getContentSize().height*0.5), map->getContentSize());

	for (int i = 0; i < 4; i++)
	{
		//如果出界了
		if (!map_rect.containsPoint(vec[i]))
		{
			return false;
		}
		Vec2 tile_point = gamelayer->convert_to_map(vec[i]);
		int gid = map->getLayer("layer_0")->getTileGIDAt(tile_point);
		Common::TileType tt = Common::getTileType(gid);
		if (tt== Common::TileType::BLOCK||tt== Common::TileType::STEEL)
		{
			return false;
		}
	}
	return true;
}

void Tank_Friends::move()
{
	if (_dir == Common::Dir_Control::Up)
	{
		Common::moveNodeY(this, _speed);
	}
	if (_dir == Common::Dir_Control::Down)
	{
		Common::moveNodeY(this, -_speed);
	}
	if (_dir == Common::Dir_Control::Left)
	{
		Common::moveNodeX(this, -_speed);
	}
	if (_dir == Common::Dir_Control::Right)
	{
		Common::moveNodeX(this, _speed);
	}
}

void Tank_Friends::turn(Common::Dir_Control dir)
{
	this->setRotation(dir * 90);
	this->_dir = dir;
}