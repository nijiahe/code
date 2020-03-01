#ifndef __Organism_H__
#define __Organism_H__

#include "Common.h"

class Game_Layer;
class Mario_Player;

class Organism:public Sprite
{
public:
	bool init();
	virtual ~Organism();

	virtual void birth(Vec2 vec);
	virtual void set_picture() = 0;
	virtual void set_physics();//设置小人状态的属性
	virtual void moveleft_ctl();
	virtual void moveright_ctl();
	virtual void moveleft();
	virtual void moveright();
	virtual void jump();
	virtual void Top_To_Collosion_monitor(float t);
	virtual void jump_monitor(float t);
	virtual void move_monitor(float t);
	//died_monitor也必须重载
	virtual void died_monitor(float t);
	virtual void monitor_switch(float t);
	virtual void run_monitor_switch();
	virtual void start_monitor();
	virtual void stop_monitor();
	virtual void clean() = 0;
	/*这两个虚函数:左右移动*/
	virtual void play_new_left_move_action();
	virtual void play_new_right_move_action();

	//
	virtual void auto_move(float t);
	virtual void auto_jump(float t);
	//
	TMXTiledMap * getmap();
	Game_Layer * getgamelayer();
	Mario_Player * get_mario();
	float get_gravity();

	bool will_outofmap();
	bool standing_on_something();
	Common::Tile_Type left_foot_standing_on_something();
	Common::Tile_Type right_foot_standing_on_something();
	Common::Tile_Type left_leaning_on_something();
	Common::Tile_Type right_leaning_on_something();
	Common::Tile_Type Left_Top_To_something();
	Common::Tile_Type Right_Top_To_something();
	Sprite * get_Left_Top_to();
	Sprite * get_Right_Top_to();
	
	bool collision_by_God_tortoise();
	void jump_autoadjust();
	void moveleft_autojust();
	void moveright_autojust();
	Rect getnext_Frame_boundingbox_onmap();
	Rect getnow_Frame_boundingbox_onmap();
	Vec2 Convert_To_Map_Position(Vec2 point);
	Vec2 get_Next_Frame_Left_Head_Positon();
	Vec2 get_Next_Frame_Right_Head_Positon();
	Vec2 get_Next_Frame_Left_Head_Tile_Positon();
	Vec2 get_Next_Frame_Right_Head_Tile_Positon();

	Rect Convert_To_Rect(Vec2 tile);
	Rect getmapboundingbox();
	void setGod_schedule(float t);
	void unsetGod_schedule(float t);
	virtual void play_God_action(float t);

	float _left_right_move_power;//左右移动力量
	float _jump_power;//弹跳力
	float _jump_anti_power;//跳跃反震力,即被踩了之后给踩的人多少跳跃力
	float _left_speed = 0;//当前左边速度
	float _right_speed = 0;//当前右边速度
	float _jump_speed = 0;//当前向上跳的速度
	float _down_speed = 0;//当前向下降的速度
	Common::Face_dir _face_dir;//脸朝向
	bool _is_moving_left = false;
	bool _is_moving_right = false;
	bool _is_jump = false;
	bool _monitor_work = false;
	bool isGod = false;
};

#endif