#ifndef __Player_H__
#define __Player_H__

#include <WinSock2.h>
#include "Chess_Color.h"

#include "cocos2d.h"
#include "Chesspiece.h"
#include "Chess_Step.h"
USING_NS_CC;

class Chess_Board;
class Chesspiece;
class Chess_Step;

class PLayer:public Node
{
public:
	PLayer();
	//游戏逻辑
	void start_play(Chess_Board * _chess);
	void add_my_all_chess();//添加我方方棋子
	void add_other_all_chess();//添加对方棋子

	Chess_Board * _chess;//棋盘
	Chess_Color _chess_color;//所持子颜色
	Chess_Step * _current_step=nullptr;
	Vector<Chesspiece *> _chess_vector;//现有棋子
	Vector<Chesspiece *> _cemetery;//墓地
	Vector<Chess_Step *> _chess_step_vector;
};
#endif

