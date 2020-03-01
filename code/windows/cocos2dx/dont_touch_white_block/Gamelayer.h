#ifndef __Gamelayer_H__
#define __Gamelayer_H__

#include "cocos2d.h"
#include "block.h"
USING_NS_CC;

class Gamelayer :public LayerColor
{
public:
	CREATE_FUNC(Gamelayer);
	bool init();
	static Scene* createscene();
	void add_white_block(Vec2 position);
	void add_black_block(Vec2 position);
	void add_gamestart_block(Vec2 position);
	void add_gameover_block(Vec2 position);
	void add_block_line();
	void start_layer_prepare();
	void runtouch_nextline(float height);
	void autoshrink_blockvector();

	void add_game_end_menu();
	void quit_menu_callback(Ref* ref);
	void playagain_menu_callback(Ref* ref);
	enum block_type
	{
		white_block,
		black_block,
		gamestart_block,
		gameover_block,
	};
	enum
	{
		ttflbtag,
	};
	void auto_add(block_type type);

	void run_schedule();
	void stop_schedule();
	void time_schedule(float dt);
	void set_timeschedule();
	float schedule_time = 0;

	bool isover = false;
	int line_count;
	Vector<block*> block_vector;
	Size winsize;
};
#endif