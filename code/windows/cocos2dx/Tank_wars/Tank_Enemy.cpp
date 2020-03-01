#include "Tank_Enemy.h"
#include "Bullet_Enemy.h"
#include "Game_Layer.h"

bool Tank_Enemy::init(Common::Enemy_Tank_Type type)
{
	if (!Tank::init())
	{
		return false;
	}

	_type = type;
	if (_type == Common::Enemy_Tank_Type::Green_panzer)
	{
		set_picture("tank/armor/armor3U.png");
		physics_init(3, 1, 1);
	}
	else if (_type == Common::Enemy_Tank_Type::Green_speed_tank)
	{
		set_picture("tank/speed/speedU.png");
		physics_init(1, 1, 2);
	}
	else if (_type == Common::Enemy_Tank_Type::Red_normal_tank)
	{
		set_picture("tank/normal/normalU_R.png");
		physics_init(1, 1, 1);
	}
	else if (_type == Common::Enemy_Tank_Type::Red_panzer)
	{
		set_picture("tank/armor/armor3U_R.png");
		physics_init(3, 1, 1);
	}
	else if (_type == Common::Enemy_Tank_Type::Red_speed_tank)
	{
		set_picture("tank/speed/speedU_R.png");
		physics_init(1, 1, 2);
	}
	else if (_type == Common::Enemy_Tank_Type::White_normal_tank)
	{
		set_picture("tank/normal/normalU.png");
		physics_init(1, 1, 1);
	}

	turn(Common::Dir_Control::Down);
	

	return true;
}

int Tank_Enemy::get_score()
{
	if (_type == Common::Enemy_Tank_Type::Green_panzer || _type == Common::Enemy_Tank_Type::Red_panzer)
	{
		return 400;
	}
	else if (_type == Common::Enemy_Tank_Type::Green_speed_tank || _type == Common::Enemy_Tank_Type::Red_speed_tank)
	{
		return 200;
	}
	else if (_type == Common::Enemy_Tank_Type::Red_normal_tank || _type == Common::Enemy_Tank_Type::White_normal_tank)
	{
		return 100;
	}
	return 0;
}

void Tank_Enemy::injured()
{
	Game_Layer * gamelayer = (Game_Layer *)getParent()->getParent();
	TMXTiledMap * map = gamelayer->_map;
	_life--;
	if (_type == Common::Enemy_Tank_Type::Green_panzer&&_life == 2|| _type == Common::Enemy_Tank_Type::Red_panzer&&_life==2)
	{
		set_picture("tank/armor/armor2U.png");
		setContentSize(Size(map->getTileSize().width*2, map->getTileSize().height*2));
		turn(_dir);
	}
	else if (_type == Common::Enemy_Tank_Type::Green_panzer&&_life == 1 || _type == Common::Enemy_Tank_Type::Red_panzer&&_life == 1)
	{
		set_picture("tank/armor/armor1U.png");
		setContentSize(Size(map->getTileSize().width*2, map->getTileSize().height * 2));
		turn(_dir);
	}
}

Bullet_Enemy * Tank_Enemy::shoot()
{
	Bullet_Enemy* bullet = Bullet_Enemy::create();
	bullet->set_picture("tank/bullet.png");
	Vec2 head_point;
	int speed = 4;
	if (_dir == Common::Dir_Control::Up)
	{
		head_point.x = getPosition().x;
		head_point.y = getPosition().y + getContentSize().height*0.5;

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
		head_point.x = getPosition().x - getContentSize().width*0.5;
		head_point.y = getPosition().y;
		bullet->runAction(MoveBy::create(Winsize.width / 4 / 60, Vec2(-Winsize.width, 0)));
	}
	if (_dir == Common::Dir_Control::Right)
	{
		head_point.x = getPosition().x + getContentSize().width*0.5;
		head_point.y = getPosition().y;
		bullet->runAction(MoveBy::create(Winsize.width / 4 / 60, Vec2(Winsize.width, 0)));
	}

	bullet->setPosition(head_point);

	return bullet;
}

Tank_Enemy * Tank_Enemy::create(Common::Enemy_Tank_Type type)
{
	Tank_Enemy * tank = new Tank_Enemy;
	if (tank&&tank->init(type))
	{
		tank->autorelease();
	}
	else
	{
		delete(tank);
		tank = NULL;
	}
	return tank;
}
