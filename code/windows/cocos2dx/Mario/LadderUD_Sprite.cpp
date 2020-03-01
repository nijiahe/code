#include "LadderUD_Sprite.h"
#include "Game_Layer.h"
#include "Mario_Player.h"

bool LadderUD_Sprite::init()
{
	if (!Organism::init())
	{
		return false;
	}
	set_picture();
	set_physics();
	_face_dir = Common::Face_dir::Left;

	schedule(SEL_SCHEDULE(&LadderUD_Sprite::monitor_switch));

	return true;
}


void LadderUD_Sprite::died_monitor(float t)
{
	Game_Layer * layer = getgamelayer();
	for (int i = 0; i < layer->_organism_vec.size(); i++)
	{
		Organism * organism = layer->_organism_vec.at(i);
		Rect next_rect = organism->getnext_Frame_boundingbox_onmap();
		float scale = 0.5f;
		Rect body_rect = Rect(next_rect.getMinX(), next_rect.getMinY() + next_rect.size.height*scale, next_rect.size.width, next_rect.size.height*(1 - scale));
		Rect foot_rect = Rect(next_rect.getMinX(), next_rect.getMinY(), next_rect.size.width, next_rect.size.height*scale);


		if (this->getnext_Frame_boundingbox_onmap().intersectsRect(foot_rect) &&
			!this->getnext_Frame_boundingbox_onmap().intersectsRect(body_rect))
		{
			organism->_down_speed = 0;

			if (_is_down)
			{
				Common::MoveNode(organism, Vec2(0, -_jump_power));
			}
			else
			{
				Common::MoveNode(organism, Vec2(0, _jump_power));
			}
		}
	}

}

void LadderUD_Sprite::auto_move(float t)
{
	if (_is_down)
	{
		Common::MoveNode(this, Vec2(0, -_jump_power));
		_height -= _jump_power;
		if (_height <= _height_min)
		{
			_is_down = false;
		}
	}
	else
	{
		Common::MoveNode(this, Vec2(0, _jump_power));
		_height += _jump_power;
		if (_height >= _height_max)
		{
			_is_down = true;
		}
	}
}


void LadderUD_Sprite::start_monitor()
{
	if (!_monitor_work)
	{
		//上下方向速度检测
		schedule(SEL_SCHEDULE(&LadderUD_Sprite::jump_monitor));
		//左右方向速度检测
		schedule(SEL_SCHEDULE(&LadderUD_Sprite::move_monitor));
		//自动行走检测
		schedule(SEL_SCHEDULE(&LadderUD_Sprite::auto_move));
		//死亡检测
		schedule(SEL_SCHEDULE(&LadderUD_Sprite::died_monitor));

		_monitor_work = true;
	}
}
void LadderUD_Sprite::stop_monitor()
{
	if (_monitor_work)
	{
		//上下方向速度检测
		unschedule(SEL_SCHEDULE(&LadderUD_Sprite::jump_monitor));
		//左右方向速度检测
		unschedule(SEL_SCHEDULE(&LadderUD_Sprite::move_monitor));
		//自动行走检测
		unschedule(SEL_SCHEDULE(&LadderUD_Sprite::auto_move));
		//死亡检测
		unschedule(SEL_SCHEDULE(&LadderUD_Sprite::died_monitor));
		_monitor_work = false;
	}
}