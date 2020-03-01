#include "Organism.h"
#include "Game_Layer.h"
#include "Mario_Player.h"
#include "Tortoise.h"
#include "Ladder_Base.h"

bool Organism::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	setLocalZOrder(100);
	_face_dir = Common::Face_dir::Right;
	_is_moving_left = false;
	_is_moving_right = false;

	return true;
}

Rect Organism::getmapboundingbox()
{
	return Rect(Vec2(0, 0), getmap()->getContentSize());
}

Rect Organism::Convert_To_Rect(Vec2 tile)
{
	TMXTiledMap * map = getmap();
	int min_x;
	int max_y;
	min_x = tile.x * map->getTileSize().width;
	max_y = (map->getMapSize().height - tile.y)*map->getTileSize().height;
	return Rect(Vec2(min_x, max_y - map->getTileSize().height), map->getTileSize());
}

Vec2 Organism::Convert_To_Map_Position(Vec2 point)
{
	TMXTiledMap * map = getmap();
	if (!getmapboundingbox().containsPoint(point))
	{
		return Vec2(0, 0);
	}
	int map_x = 0;
	int map_y = 0;
	Size tile_size = map->getTileSize();
	Size map_size = map->getMapSize();
	map_x = point.x / tile_size.width;
	map_y = (map->getContentSize().height - point.y) / tile_size.height;
	Vec2 res_position = Vec2(map_x, map_y);

	return res_position;
}

Vec2 Organism::get_Next_Frame_Left_Head_Positon()
{
	Rect rect = getnext_Frame_boundingbox_onmap();
	return Vec2(rect.getMinX(), rect.getMaxY());
}

Vec2 Organism::get_Next_Frame_Right_Head_Positon()
{
	Rect rect = getnext_Frame_boundingbox_onmap();
	return Vec2(rect.getMaxX(), rect.getMaxY());
}

Vec2 Organism::get_Next_Frame_Left_Head_Tile_Positon()
{
	Vec2 vec = Convert_To_Map_Position(get_Next_Frame_Left_Head_Positon());
	return Vec2(vec.x , vec.y - 1);
}

Vec2 Organism::get_Next_Frame_Right_Head_Tile_Positon()
{
	Vec2 vec = Convert_To_Map_Position(get_Next_Frame_Right_Head_Positon());
	return Vec2(vec.x, vec.y - 1);
}

void Organism::jump_autoadjust()
{
	Rect now_Frame_boundingbox = getnow_Frame_boundingbox_onmap();
	Vec2 foot[2];
	foot[0] = Vec2(now_Frame_boundingbox.getMinX(), now_Frame_boundingbox.getMinY());
	foot[1] = Vec2(now_Frame_boundingbox.getMaxX(), now_Frame_boundingbox.getMinY());
	for (int i = 0; i < 2; i++)
	{
		Vec2 now_Frame_foot_tile = Convert_To_Map_Position(foot[i]);
		Rect rect = Convert_To_Rect(now_Frame_foot_tile);
		this->setPositionY(rect.getMaxY());
	}
}

void Organism::moveleft_autojust()
{
	Rect now_Frame_boundingbox = getnow_Frame_boundingbox_onmap();
	Vec2 left_body[2];

	left_body[0] = Vec2(now_Frame_boundingbox.getMinX(), now_Frame_boundingbox.getMinY());
	left_body[1] = Vec2(now_Frame_boundingbox.getMinX(), now_Frame_boundingbox.getMaxY());
	for (int i = 0; i < 2; i++)
	{
		Vec2 now_Frame_left_body_tile = Convert_To_Map_Position(left_body[i]);
		Rect rect = Convert_To_Rect(now_Frame_left_body_tile);
		this->setPositionX(rect.getMaxX()+1);
	}
}
void Organism::moveright_autojust()
{
	Rect now_Frame_boundingbox = getnow_Frame_boundingbox_onmap();
	Vec2 right_body[2];

	right_body[0] = Vec2(now_Frame_boundingbox.getMaxX(), now_Frame_boundingbox.getMinY());
	right_body[1] = Vec2(now_Frame_boundingbox.getMaxX(), now_Frame_boundingbox.getMaxY());
	for (int i = 0; i < 2; i++)
	{
		Vec2 now_Frame_right_body_tile = Convert_To_Map_Position(right_body[i]);
		Rect rect = Convert_To_Rect(now_Frame_right_body_tile);
		
		this->setPositionX(rect.getMinX()-this->getContentSize().width-1);
	}
}

bool Organism::collision_by_God_tortoise()
{
	Game_Layer * layer = getgamelayer();
	for (int i = 0; i < layer->_tortoise_vec.size(); i++)
	{
		Tortoise * tortoise = layer->_tortoise_vec.at(i);
		if (this->getnow_Frame_boundingbox_onmap().intersectsRect(tortoise->getnow_Frame_boundingbox_onmap()))
		{
			if (tortoise->isGod && (tortoise->_is_moving_left || tortoise->_is_moving_right))
			{
				return true;
			}
		}
		
	}
	return false;
}

void Organism::Top_To_Collosion_monitor(float t)
{
	Common::Tile_Type tile_type1 = this->Left_Top_To_something();
	Common::Tile_Type tile_type2 = this->Right_Top_To_something();
	if (
		(tile_type1 != Common::Tile_Type::None &&tile_type2!= Common::Tile_Type::None)
		|| this->will_outofmap())
	{
		this->_jump_speed = 0;
	}
}


Sprite * Organism::get_Left_Top_to()
{
	TMXTiledMap * map = getmap();
	TMXLayer * block_layer = map->getLayer("block");
	TMXLayer * land_layer = map->getLayer("land");
	TMXLayer * pipe_layer = map->getLayer("pipe");
	Rect next_Frame_boundingbox = getnext_Frame_boundingbox_onmap();
	Vec2 head;
	Vec2 next_Frame_left_head = Vec2(next_Frame_boundingbox.getMinX(), next_Frame_boundingbox.getMaxY());
	head = Convert_To_Map_Position(next_Frame_left_head);
	head.setPoint(head.x, head.y - 1);

	Sprite * block_layer_spr = block_layer->getTileAt(head);
	if (block_layer_spr)
	{
		return block_layer_spr;
	}
	Sprite * land_layer_spr = land_layer->getTileAt(head);
	if (land_layer_spr)
	{
		return land_layer_spr;
	}
	Sprite * pipe_layer_spr = pipe_layer->getTileAt(head);
	if (pipe_layer_spr)
	{
		return pipe_layer_spr;
	}
	
	return NULL;
}

Sprite * Organism::get_Right_Top_to()
{
	TMXTiledMap * map = getmap();
	TMXLayer * block_layer = map->getLayer("block");
	TMXLayer * land_layer = map->getLayer("land");
	TMXLayer * pipe_layer = map->getLayer("pipe");
	Rect next_Frame_boundingbox = getnext_Frame_boundingbox_onmap();
	Vec2 head;
	Vec2 next_Frame_left_head = Vec2(next_Frame_boundingbox.getMaxX(), next_Frame_boundingbox.getMaxY());
	head = Convert_To_Map_Position(next_Frame_left_head);
	head.setPoint(head.x, head.y - 1);

	Sprite * block_layer_spr = block_layer->getTileAt(head);
	if (block_layer_spr)
	{
		return block_layer_spr;
	}
	Sprite * land_layer_spr = land_layer->getTileAt(head);
	if (land_layer_spr)
	{
		return land_layer_spr;
	}
	Sprite * pipe_layer_spr = pipe_layer->getTileAt(head);
	if (pipe_layer_spr)
	{
		return pipe_layer_spr;
	}

	return NULL;
}

Common::Tile_Type Organism::Right_Top_To_something()
{
	TMXTiledMap * map = getmap();
	TMXLayer * block_layer = map->getLayer("block");
	TMXLayer * land_layer = map->getLayer("land");
	TMXLayer * pipe_layer = map->getLayer("pipe");
	Rect next_Frame_boundingbox = getnext_Frame_boundingbox_onmap();
	Vec2 head;
	Vec2 next_Frame_left_head = Vec2(next_Frame_boundingbox.getMaxX(), next_Frame_boundingbox.getMaxY());
	head = Convert_To_Map_Position(next_Frame_left_head);

	int block_layer_gid = block_layer->getTileGIDAt(head);
	int land_layer_gid = land_layer->getTileGIDAt(head);
	int pipe_layer_gid = pipe_layer->getTileGIDAt(head);

	if (Common::Convert_Gid_To_Type(block_layer_gid) == Common::Tile_Type::Tub_Block)
	{
		return Common::Tile_Type::Tub_Block;
	}
	else if (Common::Convert_Gid_To_Type(block_layer_gid) == Common::Tile_Type::Solid_Block)
	{
		return Common::Tile_Type::Solid_Block;
	}
	else if (Common::Convert_Gid_To_Type(land_layer_gid) == Common::Tile_Type::Land)
	{
		return Common::Tile_Type::Land;
	}
	else if (Common::Convert_Gid_To_Type(pipe_layer_gid) == Common::Tile_Type::Pipe)
	{
		return Common::Tile_Type::Pipe;
	}


	return Common::Tile_Type::None;
}

Common::Tile_Type Organism::Left_Top_To_something()
{
	TMXTiledMap * map = getmap();
	TMXLayer * block_layer = map->getLayer("block");
	TMXLayer * land_layer = map->getLayer("land");
	TMXLayer * pipe_layer = map->getLayer("pipe");
	Rect next_Frame_boundingbox = getnext_Frame_boundingbox_onmap(); 
	Vec2 head;
	Vec2 next_Frame_left_head = Vec2(next_Frame_boundingbox.getMinX(), next_Frame_boundingbox.getMaxY());
	head = Convert_To_Map_Position(next_Frame_left_head);

	int block_layer_gid = block_layer->getTileGIDAt(head);
	int land_layer_gid = land_layer->getTileGIDAt(head);
	int pipe_layer_gid = pipe_layer->getTileGIDAt(head);
		
	if (Common::Convert_Gid_To_Type(block_layer_gid) == Common::Tile_Type::Tub_Block)
	{
		return Common::Tile_Type::Tub_Block;
	}
	else if (Common::Convert_Gid_To_Type(block_layer_gid) == Common::Tile_Type::Solid_Block)
	{
		return Common::Tile_Type::Solid_Block;
	}
	else if (Common::Convert_Gid_To_Type(land_layer_gid) == Common::Tile_Type::Land)
	{
		return Common::Tile_Type::Land;
	}
	else if (Common::Convert_Gid_To_Type(pipe_layer_gid) == Common::Tile_Type::Pipe)
	{
		return Common::Tile_Type::Pipe;
	}


	return Common::Tile_Type::None;
}

Common::Tile_Type Organism::left_leaning_on_something()
{
	TMXTiledMap * map = getmap();
	TMXLayer * block_layer = map->getLayer("block");
	TMXLayer * land_layer = map->getLayer("land");
	TMXLayer * pipe_layer = map->getLayer("pipe");
	TMXLayer * flagpole_layer = map->getLayer("flagpole");

	Rect mario_boundingbox = getnext_Frame_boundingbox_onmap();
	Vec2 left[2];
	left[0] = Vec2(mario_boundingbox.getMinX(), mario_boundingbox.getMaxY());
	left[1] = Vec2(mario_boundingbox.getMinX(), mario_boundingbox.getMinY()+1);
	for (int i = 0; i < 2; i++)
	{
		Vec2 map_place = Convert_To_Map_Position(left[i]);
		int block_layer_gid = block_layer->getTileGIDAt(map_place);
		int land_layer_gid = land_layer->getTileGIDAt(map_place);
		int pipe_layer_gid = pipe_layer->getTileGIDAt(map_place);
		int flagpole_layer_gid = flagpole_layer->getTileGIDAt(map_place);

		if (Common::Convert_Gid_To_Type(block_layer_gid) == Common::Tile_Type::Tub_Block)
		{
			return Common::Tile_Type::Tub_Block;
		}
		else if (Common::Convert_Gid_To_Type(block_layer_gid) == Common::Tile_Type::Solid_Block)
		{
			return Common::Tile_Type::Solid_Block;
		}
		else if (Common::Convert_Gid_To_Type(land_layer_gid) == Common::Tile_Type::Land)
		{
			return Common::Tile_Type::Land;
		}
		else if (Common::Convert_Gid_To_Type(pipe_layer_gid) == Common::Tile_Type::Pipe)
		{
			return Common::Tile_Type::Pipe;
		}
		else if (Common::Convert_Gid_To_Type(flagpole_layer_gid) == Common::Tile_Type::Flagpole)
		{
			return Common::Tile_Type::Flagpole;
		}
	}
	return Common::Tile_Type::None;
}

Common::Tile_Type Organism::right_leaning_on_something()
{
	TMXTiledMap * map = getmap();
	TMXLayer * block_layer = map->getLayer("block");
	TMXLayer * land_layer = map->getLayer("land");
	TMXLayer * pipe_layer = map->getLayer("pipe");
	TMXLayer * flagpole_layer = map->getLayer("flagpole");

	Rect mario_boundingbox = getnext_Frame_boundingbox_onmap();
	Vec2 right[2];
	right[0] = Vec2(mario_boundingbox.getMaxX(), mario_boundingbox.getMaxY());
	right[1] = Vec2(mario_boundingbox.getMaxX(), mario_boundingbox.getMinY()+1);
	for (int i = 0; i < 2; i++)
	{
		Vec2 map_place = Convert_To_Map_Position(right[i]);
		int block_layer_gid = block_layer->getTileGIDAt(map_place);
		int land_layer_gid = land_layer->getTileGIDAt(map_place);
		int pipe_layer_gid = pipe_layer->getTileGIDAt(map_place);
		int flagpole_layer_gid = flagpole_layer->getTileGIDAt(map_place);

		if (Common::Convert_Gid_To_Type(block_layer_gid) == Common::Tile_Type::Tub_Block)
		{
			return Common::Tile_Type::Tub_Block;
		}
		else if (Common::Convert_Gid_To_Type(block_layer_gid) == Common::Tile_Type::Solid_Block)
		{
			return Common::Tile_Type::Solid_Block;
		}
		else if (Common::Convert_Gid_To_Type(land_layer_gid) == Common::Tile_Type::Land)
		{
			return Common::Tile_Type::Land;
		}
		else if (Common::Convert_Gid_To_Type(pipe_layer_gid) == Common::Tile_Type::Pipe)
		{
			return Common::Tile_Type::Pipe;
		}
		else if (Common::Convert_Gid_To_Type(flagpole_layer_gid) == Common::Tile_Type::Flagpole)
		{
			return Common::Tile_Type::Flagpole;
		}

	}
	return Common::Tile_Type::None;
}

Common::Tile_Type Organism::left_foot_standing_on_something()
{
	TMXTiledMap * map = getmap();
	TMXLayer * block_layer = map->getLayer("block");
	TMXLayer * land_layer = map->getLayer("land");
	TMXLayer * pipe_layer = map->getLayer("pipe");
	Rect now_Frame_boundingbox = getnow_Frame_boundingbox_onmap();
	Vec2 now_Frame_left_foot = Vec2(now_Frame_boundingbox.getMinX() + 1, now_Frame_boundingbox.getMinY());
	Vec2 now_Frame_left_foot_tile = Convert_To_Map_Position(now_Frame_left_foot);
	int left_block_layer_gid = block_layer->getTileGIDAt(now_Frame_left_foot_tile);
	int left_land_layer_gid = land_layer->getTileGIDAt(now_Frame_left_foot_tile);
	int left_pipe_layer_gid = pipe_layer->getTileGIDAt(now_Frame_left_foot_tile);

	if (Common::Convert_Gid_To_Type(left_block_layer_gid) == Common::Tile_Type::Tub_Block)
	{
		return Common::Tile_Type::Tub_Block;
	}
	else if (Common::Convert_Gid_To_Type(left_block_layer_gid) == Common::Tile_Type::Solid_Block)
	{
		return Common::Tile_Type::Solid_Block;
	}
	else if (Common::Convert_Gid_To_Type(left_land_layer_gid) == Common::Tile_Type::Land)
	{
		return Common::Tile_Type::Land;
	}
	else if (Common::Convert_Gid_To_Type(left_pipe_layer_gid) == Common::Tile_Type::Pipe)
	{
		return Common::Tile_Type::Pipe;
	}

	Game_Layer * layer = getgamelayer();
	for (int i = 0; i < layer->_labber_vec.size(); i++)
	{
		
		Ladder_Base * ladder = layer->_labber_vec.at(i);
		if (ladder->getnow_Frame_boundingbox_onmap().containsPoint(now_Frame_left_foot))
		{
			return Common::Tile_Type::Pipe;
		}
	}

	return Common::Tile_Type::None;
}

Common::Tile_Type Organism::right_foot_standing_on_something()
{
	TMXTiledMap * map = getmap();
	TMXLayer * block_layer = map->getLayer("block");
	TMXLayer * land_layer = map->getLayer("land");
	TMXLayer * pipe_layer = map->getLayer("pipe");
	Rect now_Frame_boundingbox = getnow_Frame_boundingbox_onmap();
	
	Vec2 now_Frame_right_foot = Vec2(now_Frame_boundingbox.getMaxX() - 1, now_Frame_boundingbox.getMinY());
	Vec2 now_Frame_right_foot_tile = Convert_To_Map_Position(now_Frame_right_foot);

	int right_block_layer_gid = block_layer->getTileGIDAt(now_Frame_right_foot_tile);
	int right_land_layer_gid = land_layer->getTileGIDAt(now_Frame_right_foot_tile);
	int right_pipe_layer_gid = pipe_layer->getTileGIDAt(now_Frame_right_foot_tile);

	if (Common::Convert_Gid_To_Type(right_block_layer_gid) == Common::Tile_Type::Tub_Block)
	{
		return Common::Tile_Type::Tub_Block;
	}
	else if (Common::Convert_Gid_To_Type(right_block_layer_gid) == Common::Tile_Type::Solid_Block)
	{
		return Common::Tile_Type::Solid_Block;
	}
	else if (Common::Convert_Gid_To_Type(right_land_layer_gid) == Common::Tile_Type::Land)
	{
		return Common::Tile_Type::Land;
	}
	else if (Common::Convert_Gid_To_Type(right_pipe_layer_gid) == Common::Tile_Type::Pipe)
	{
		return Common::Tile_Type::Pipe;
	}

	Game_Layer * layer = getgamelayer();
	for (int i = 0; i < layer->_labber_vec.size(); i++)
	{

		Ladder_Base * ladder = layer->_labber_vec.at(i);
		if (ladder->getnow_Frame_boundingbox_onmap().containsPoint(now_Frame_right_foot))
		{
			return Common::Tile_Type::Pipe;
		}
	}

	return Common::Tile_Type::None;
}

bool Organism::standing_on_something()
{
	TMXTiledMap * map = getmap();
	TMXLayer * block_layer = map->getLayer("block");
	TMXLayer * land_layer = map->getLayer("land");
	TMXLayer * pipe_layer = map->getLayer("pipe");
	Rect now_Frame_boundingbox = getnow_Frame_boundingbox_onmap();
	Vec2 world_foot[2];
	world_foot[0] = Vec2(now_Frame_boundingbox.getMinX()+1, now_Frame_boundingbox.getMinY());
	world_foot[1] = Vec2(now_Frame_boundingbox.getMaxX()-1, now_Frame_boundingbox.getMinY());
	Vec2 foot[2];
	foot[0] = Convert_To_Map_Position(world_foot[0]);
	foot[1] = Convert_To_Map_Position(world_foot[1]);
	for (int i = 0; i < 2; i++)
	{
		int left_block_layer_gid = block_layer->getTileGIDAt(foot[i]);
		int left_land_layer_gid = land_layer->getTileGIDAt(foot[i]);
		int left_pipe_layer_gid = pipe_layer->getTileGIDAt(foot[i]);
		if (Common::Convert_Gid_To_Type(left_block_layer_gid) == Common::Tile_Type::Tub_Block)
		{
			return true;
		}
		else if (Common::Convert_Gid_To_Type(left_block_layer_gid) == Common::Tile_Type::Solid_Block)
		{
			return true;
		}
		else if (Common::Convert_Gid_To_Type(left_land_layer_gid) == Common::Tile_Type::Land)
		{
			return true;
		}
		else if (Common::Convert_Gid_To_Type(left_pipe_layer_gid) == Common::Tile_Type::Pipe)
		{
			return true;
		}
		Game_Layer * layer = getgamelayer();
		for (int j = 0; j < layer->_labber_vec.size(); j++)
		{
			Ladder_Base * ladder = layer->_labber_vec.at(j);
			if (ladder->getnow_Frame_boundingbox_onmap().containsPoint(world_foot[i]))
			{
				return true;
			}
		}
	}

	return false;
}

Rect Organism::getnext_Frame_boundingbox_onmap()
{
	Rect rect = getnow_Frame_boundingbox_onmap();
	if (_face_dir == Common::Face_dir::Left)
	{
		rect.setRect(rect.getMinX() - _left_speed, rect.getMinY(), this->getContentSize().width, this->getContentSize().height);
	}
	else if (_face_dir == Common::Face_dir::Right)
	{
		rect.setRect(rect.getMinX() + _right_speed, rect.getMinY(), this->getContentSize().width, this->getContentSize().height);
	}
	if (_jump_speed != 0)
	{
		rect.setRect(rect.getMinX(), rect.getMinY() + _jump_speed - get_gravity() * 1 / 60, this->getContentSize().width, this->getContentSize().height);
	}
	else if (_down_speed != 0)
	{
		rect.setRect(rect.getMinX(), rect.getMinY() - _down_speed - get_gravity()*1/60, this->getContentSize().width, this->getContentSize().height);
	}
	return rect;
}

Rect Organism::getnow_Frame_boundingbox_onmap()
{
	TMXTiledMap * map = getmap();
	Rect rect = this->getBoundingBox();
	Vec2 origin_place = Vec2(rect.getMinX(), rect.getMinY());
	Rect res_rect = Rect(origin_place, this->getContentSize());

	return res_rect;
}

void Organism::moveleft_ctl()
{
	this->_face_dir = Common::Face_dir::Left;
	this->_is_moving_right = false;
	this->_left_speed += this->_left_right_move_power;
}
void Organism::moveright_ctl()
{
	this->_face_dir = Common::Face_dir::Right;
	this->_is_moving_left = false;
	this->_right_speed += this->_left_right_move_power;
}

void Organism::jump()
{
	if (this->standing_on_something())
	{
		this->_jump_speed = this->_jump_power;
	}
}

void Organism::moveleft()
{
	if (!will_outofmap() && 
		(left_leaning_on_something() == Common::Tile_Type::None || left_leaning_on_something() == Common::Tile_Type::Flagpole))
	{
		Common::MoveNode(this, Vec2(-this->_left_speed, 0));
	}
	if (!_is_moving_left)
	{
		play_new_left_move_action();
		_is_moving_left = true;
		_is_moving_right = false;
	}
	_left_speed = 0;
}

void Organism::moveright()
{
	if (!will_outofmap() && 
		(right_leaning_on_something() == Common::Tile_Type::None|| right_leaning_on_something() == Common::Tile_Type::Flagpole))
	{
		Common::MoveNode(this, Vec2(this->_right_speed, 0));
	}
	if (!_is_moving_right)
	{
		play_new_right_move_action();
		_is_moving_left = false;
		_is_moving_right = true;
	}
	_right_speed = 0;
}

void Organism::start_monitor()
{
	if (!_monitor_work)
	{
		//上下方向速度检测
		schedule(SEL_SCHEDULE(&Organism::jump_monitor));
		//左右方向速度检测
		schedule(SEL_SCHEDULE(&Organism::move_monitor));
		//受伤死亡检测
		schedule(SEL_SCHEDULE(&Organism::died_monitor));
		//头顶碰撞检测
		schedule(SEL_SCHEDULE(&Organism::Top_To_Collosion_monitor));
		_monitor_work = true;
	}
}
void Organism::stop_monitor()
{
	if (_monitor_work)
	{
		//上下方向速度检测
		unschedule(SEL_SCHEDULE(&Organism::jump_monitor));
		//左右方向速度检测
		unschedule(SEL_SCHEDULE(&Organism::move_monitor));
		//受伤死亡检测
		unschedule(SEL_SCHEDULE(&Organism::died_monitor));
		//头顶碰撞检测
		unschedule(SEL_SCHEDULE(&Organism::Top_To_Collosion_monitor));
		_monitor_work = false;
	}
}

void Organism::run_monitor_switch()
{
	
}

void Organism::died_monitor(float t)
{

}

void Organism::monitor_switch(float t)
{
	TMXTiledMap * map = getmap();
	Vec2 point = map->convertToWorldSpace(this->getPosition());
	Rect rect = Rect(Vec2(-Winsize.width*0.25, 0), Size(Winsize.width*1.5, Winsize.height));
	if (rect.containsPoint(point))
	{
		start_monitor();
	}
	else
	{
		stop_monitor();
	}
}

void Organism::jump_monitor(float t)
{
	if (this->_jump_speed > 0)
	{
		_is_jump = true;
		Common::MoveNode(this, Vec2(0, this->_jump_speed));
	}
	else if (this->_down_speed > 0)
	{
		Common::MoveNode(this, Vec2(0, -this->_down_speed));
	}
}

void Organism::move_monitor(float t)
{
	if (this->_left_speed != 0)
	{
		this->moveleft();
	}
	else if (this->_right_speed != 0)
	{
		this->moveright();
	}
}

Game_Layer * Organism::getgamelayer()
{
	return (Game_Layer *)(getParent()->getParent());
}

TMXTiledMap * Organism::getmap()
{
	return (TMXTiledMap *)getParent();
}

Mario_Player * Organism::get_mario()
{
	return getgamelayer()->_mario;
}

float Organism::get_gravity()
{
	return getgamelayer()->_gravity;
}

bool Organism::will_outofmap()
{
	TMXTiledMap * map = getmap();
	Rect rect = getnext_Frame_boundingbox_onmap();
	Vec2 point[4];
	point[0] = Vec2(rect.getMinX(), rect.getMinY());
	point[1] = Vec2(rect.getMinX(), rect.getMaxY());
	point[2] = Vec2(rect.getMaxX(), rect.getMinY());
	point[3] = Vec2(rect.getMaxX(), rect.getMaxY());
	for (int i = 0; i < 4; i++)
	{
		if (!getmapboundingbox().containsPoint(point[i]))
		{
			return true;
		}
	}
	return false;
}

void Organism::play_God_action(float t)
{
	Blink * blink = Blink::create(t, 2 * t);
	blink->setTag(Common::Action_Tag::God_Action);
	runAction(blink);
}

void Organism::setGod_schedule(float t)
{
	isGod = true;
}
void Organism::unsetGod_schedule(float t)
{
	isGod = false;
}


void Organism::auto_jump(float t)
{
	_jump_speed = _jump_power;
}

void Organism::auto_move(float t)
{
	if (_face_dir == Common::Face_dir::Left)
	{
		moveleft_ctl();
		if (will_outofmap())
		{
			_face_dir = Common::Face_dir::Right;
			_left_speed = 0;
		}
		else if ((left_leaning_on_something() != Common::Tile_Type::None || left_foot_standing_on_something() == Common::Tile_Type::None)
			&&!_is_jump)
		{
			_face_dir = Common::Face_dir::Right;
			_left_speed = 0;
		}
	}
	else if (_face_dir == Common::Face_dir::Right)
	{
		moveright_ctl();
		if (will_outofmap())
		{
			_face_dir = Common::Face_dir::Left;
			_right_speed = 0;
		}
		else if ((right_leaning_on_something() != Common::Tile_Type::None || right_foot_standing_on_something() == Common::Tile_Type::None)
			&& !_is_jump)
		{
			_face_dir = Common::Face_dir::Left;
			_right_speed = 0;
		}
	}
}

void Organism::play_new_left_move_action()
{

}

void Organism::play_new_right_move_action()
{

}

void Organism::set_physics()
{
	
}

Organism::~Organism()
{

}

void Organism::birth(Vec2 vec)
{
	getgamelayer()->_organism_vec.pushBack(this);
}