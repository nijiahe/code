#ifndef __Chess_Board_H__
#define __Chess_Board_H__

#include "cocos2d.h"
USING_NS_CC;

#include "Chess_Color.h"

class Chesspiece_Place;
class Chesspiece;
class PLayer;
class Chess_Step;

class Chess_Board:public LayerColor
{
public:
	CREATE_FUNC(Chess_Board);
	bool init();
	void add_chess_board_background();//添加棋盘背景图片
	static Scene * createscene();
	Chesspiece_Place Converto_Chess_Place(Vec2 position);//转换至棋子位置坐标
	Vec2 Converto_Layer_Position(Chesspiece_Place position);//转换至图层位置坐标
	void runtouch();//开启触摸
	void closetouch();//关闭触摸
	void monitor_touch();//触摸定时器
	void monitor_touch_callback(float t);//定时器回调函数
	Chess_Step * get_current_step_and_clean(PLayer * player);//得到当前玩家的步骤
	void run_step(Chess_Step * step);//执行步骤
	void monitor_notice();//通知何时该通知对面的监视器
	void notice_other_player(float t);//通知对方应该他下了
	void regret(int num);
	void return_step(Chess_Step * step);

	
	bool is_has_chesspiece(Chesspiece_Place position);//是否有棋子
	bool is_has_red_chesspiece(Chesspiece_Place position);//是否有红子
	bool is_has_black_chesspiece(Chesspiece_Place position);//是否有黑子
	bool is_has_samecolor_chesspiece(Chesspiece * chess, Chesspiece_Place position);//是否有相同颜色的棋子
	bool is_has_differentcolor_chesspiece(Chesspiece * chess, Chesspiece_Place position);//是否有不同颜色的棋子
	bool is_has_chesspiece_among(Chesspiece_Place origin_position, Chesspiece_Place des_position);//中间是否有棋子
	bool is_has_onlyone_chesspiece_among(Chesspiece_Place origin_position, Chesspiece_Place des_position);//中间是否只有一个棋子
	bool is_has_cross_river(Chesspiece * chess, Chesspiece_Place position);//是否过河
	bool is_has_outof_home(Chesspiece * chess,Chesspiece_Place position);//是否出大本营

	Chesspiece_Place get_different_jiang_position(Chesspiece * chess);//得到对方将绝对位置
	bool is_has_chesspiece(Chesspiece * chess,Chesspiece_Place position_by);//是否有棋子
	bool is_has_red_chesspiece(Chesspiece * chess,Chesspiece_Place position_by);//是否有红子
	bool is_has_black_chesspiece(Chesspiece * chess, Chesspiece_Place position_by);//是否有黑子
	bool is_has_samecolor_chesspiece_by(Chesspiece * chess, Chesspiece_Place position_by);//是否有相同颜色的棋子
	bool is_has_differentcolor_chesspiece_by(Chesspiece * chess, Chesspiece_Place position_by);//是否有相同颜色的棋子
	bool is_has_chesspiece_among(Chesspiece * origin_chess, Chesspiece * des_chess);//中间是否有棋子
	bool is_has_onlyone_chesspiece_among(Chesspiece * origin_chess, Chesspiece * des_chess);//中间是否只有一个棋子
	bool is_has_cross_river_by(Chesspiece * chess, Chesspiece_Place position_by);//是否过河
	bool is_has_outof_home_by(Chesspiece * chess, Chesspiece_Place position_by);//是否出大本营
	Chesspiece_Place get_different_jiang_position_by(Chesspiece * chess);//得到对方将相对位置
	
	bool is_has_in_cross(Chesspiece * chess);//是否身处河对面

	void switch_current_color();//切换当前下棋的颜色;
	Chesspiece * find_chesspiece_by_position(Chesspiece_Place position);//根据位置寻找棋子
	void add_select_picture(Chesspiece * select_chesspiece);//添加选中图片
	void add_red_select_picture(Chesspiece * select_chesspiece);//添加红色的选中图片

	enum tag
	{
		background_tag,
	};

	enum player_type
	{
		AI,
		People,
	};

	void draw_chessboard_test();//画线测试函数

	bool is_notice = false;
	Sprite * _background;
	Chess_Color _current_color;
	Chesspiece * _select_chesspiece;
	Sprite * _select_picture;
	Sprite * _red_select_picture;
	EventListenerTouchOneByOne* mylistener=nullptr;//用于控制触摸
	Vector<Chesspiece *> _chess_vec;
	PLayer * _me;
	PLayer * _other_player;
	player_type _player_type;
	
};

#endif

