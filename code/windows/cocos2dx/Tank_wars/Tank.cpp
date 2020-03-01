#include "Tank.h"
#include "Game_Layer.h"
#include "Tank_Friends.h"


bool Tank::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	return true;
}

void Tank::physics_init(int life, int file_power, float speed)
{
	_life = life;
	_file_power = file_power;
	_speed = speed;
}


bool Tank::canmove()
{
	Game_Layer * gamelayer = (Game_Layer *)getParent()->getParent();
	TMXTiledMap * map = gamelayer->_map;
	Vec2 des_position;

	Vec2 head_point;
	if (_dir == Common::Dir_Control::Up)
	{
		head_point.x = getPosition().x;
		head_point.y = getPosition().y + getContentSize().height*0.5;
	}
	if (_dir == Common::Dir_Control::Down)
	{
		head_point.x = getPosition().x;
		head_point.y = getPosition().y - getContentSize().height*0.5;
	}
	if (_dir == Common::Dir_Control::Left)
	{
		head_point.x = getPosition().x - getContentSize().width*0.5;
		head_point.y = getPosition().y;
	}
	if (_dir == Common::Dir_Control::Right)
	{
		head_point.x = getPosition().x + getContentSize().width*0.5;
		head_point.y = getPosition().y;
	}


	if (_dir == Common::Dir_Control::Up)
	{
		des_position = Vec2(getPosition().x, getPosition().y + _speed);
	}
	if (_dir == Common::Dir_Control::Down)
	{
		des_position = Vec2(getPosition().x, getPosition().y - _speed);
	}
	if (_dir == Common::Dir_Control::Left)
	{
		des_position = Vec2(getPosition().x - _speed, getPosition().y);
	}
	if (_dir == Common::Dir_Control::Right)
	{
		des_position = Vec2(getPosition().x + _speed, getPosition().y);
	}

	Rect rect = Rect(des_position.x - getContentSize().width*0.5, des_position.y - getContentSize().height*0.5, getContentSize().width, getContentSize().height);
	Vec2 vec[4];
	vec[0] = Vec2(rect.getMinX() + 0.01, rect.getMinY() + 0.01);
	vec[1] = Vec2(rect.getMinX() + 0.01, rect.getMaxY() - 0.01);
	vec[2] = Vec2(rect.getMaxX() - 0.01, rect.getMinY() + 0.01);
	vec[3] = Vec2(rect.getMaxX() - 0.01, rect.getMaxY() - 0.01);

	//如果前方有另外的敌军坦克
	for (int i = 0; i < gamelayer->_tank_enemy_vec.size(); i++)
	{
		//如果是这辆
		if (gamelayer->_tank_enemy_vec.at(i) == this)
		{
			continue;
		}
		if (gamelayer->_tank_enemy_vec.at(i)->getBoundingBox().containsPoint(head_point))
		{
			return false;
		}	
	}
	//如果有tank1且tank1不是这辆
	if (gamelayer->_tank_friend1 != NULL && gamelayer->_tank_friend1 != (Tank_Friends *)this)
	{
		if (gamelayer->_tank_friend1->getBoundingBox().containsPoint(head_point)) 
		{
			return false;
		}
	}

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
		if (tt == Common::TileType::BLOCK || tt == Common::TileType::STEEL||tt==Common::TileType::RIVER)
		{
			return false;
		}
	}
	return true;
}

void Tank::move()
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

void Tank::turn(Common::Dir_Control dir)
{
	this->setRotation(dir * 90);
	this->_dir = dir;
}

void Tank::set_picture(const char* filename)
{
	
	Texture2D* texture = Director::getInstance()->getTextureCache()->addImage(filename);

	setTexture(texture);
	setTextureRect(Rect(0, 0, texture->getContentSize().width, texture->getContentSize().height));
}