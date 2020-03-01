#ifndef __Game_Layer_H__
#define __Game_Layer_H__


#include "Common.h"
#include "Tank_enemy.h"

class Tank_Friends;
class Bullet_Friend;
class Tank_Enemy;
class Bullet_Enemy;
class Tank_Item;

class Game_Layer :public LayerColor
{
public:
	bool init(int index,Tank_Friends* tank_friend1 = nullptr,Tank_Friends * tank_friend2 = nullptr);
	static Game_Layer * create(int index, Tank_Friends* tank_friend1 = nullptr, Tank_Friends * tank_friend2 = nullptr);

	Vec2 convert_to_map(Vec2 position);
	Vec2 convert_to_point(Vec2 tile_point);
	void set_onmap_position(Node * node , Vec2 tile_point);
	void dir_menu_callback(Ref * ref);
	void shoot_menu_callback(Ref * ref);
	void bullet_friend_collision_detection(float t);
	void bullet_enemy_collision_detection(float t);
	void add_enemy_tank_callback(float t);
	void enemy_move_callback(float t);
	void enemy_shoot_callback(float t);
	void delete_enemy(Tank_Enemy * enemy);
	void lost();
	void lost_menu_callfunc(Ref * ref);
	void win_and_lost_callfunc(float t);
	void eat_item_callfunc(float t);
	void set_block(float t);//设置家旁边的tile为砖头
	void timer_resume_callback(float t);
	void setup_menu_callback(Ref * ref);
	

	TMXTiledMap * _map;
	Tank_Friends * _tank_friend1 = nullptr;
	Tank_Friends * _tank_friend2 = nullptr;

	Vector<Bullet_Friend *> _bullet_friend_vec;
	Vector<Bullet_Enemy *> _bullet_enemy_vec;
	Vector<Tank_Enemy *> _tank_enemy_vec;
	Vector<Tank_Item *> _tank_item_vec;
	int _index;
	int _remain_enemy=40;
	int _num = 0;//用来记录敌方坦克出生地
	Label * _tank_friend_life_label;
	Label * _tank_friend_file_power_label;
	Label * _score_label;
	Label * _remain_enemy_label;
};

#endif