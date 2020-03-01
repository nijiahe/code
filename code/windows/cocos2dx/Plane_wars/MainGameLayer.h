#ifndef __MainGameLayer_H__
#define __MainGameLayer_H__



class Plane_GameLayer;
class Bullet_GameLayer;
class Enemy_Plane_GameLayer;
class Bullet_Enemy_GameLayer;
class Game_Control_layer;
class Game_End_Layer;

#include "cocos2d.h"

USING_NS_CC;

class MainGameLayer :public LayerColor
{
public:
	CREATE_FUNC(MainGameLayer);
	bool init();
	static Scene * createscene();
	enum
	{
		background1_sprite_tag,
		background2_sprite_tag,
	};

	void add_background();
	void run_background();
	void stop_run_background();
	void background_run_callback(float t);

	void play_background_music();


	
	void add_Plane_GameLayer();
	void add_Bullet_GameLayer();
	void add_Enemy_Plane_GameLayer();
	void add_Bullet_Enemy_GameLayer();
	void add_Game_Control_Layer();
	void add_Game_End_Layer();

	Plane_GameLayer * _Plane_Layer;
	Bullet_GameLayer * _Bullet_Layer;
	Enemy_Plane_GameLayer * _Enemy_Plane_GameLayer;
	Bullet_Enemy_GameLayer * _Bullet_Enemy_GameLayer;
	Game_Control_layer * _Game_Control_layer;
	Game_End_Layer * _Game_End_Layer;
};

#endif