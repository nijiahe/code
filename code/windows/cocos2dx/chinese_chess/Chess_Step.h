#ifndef __Chess_Step_H__
#define __Chess_Step_H__

#include "Chesspiece_Place.h"
#include "cocos2d.h"
USING_NS_CC;

class Chesspiece;

class Chess_Step:public Ref
{
public:
	CREATE_FUNC(Chess_Step);
	bool init();
	Chesspiece * _move_chesspiece;//被移动的棋子
	Chesspiece_Place _origin_place;//起始位置
	Chesspiece_Place _des_place;//目标位置

	Chesspiece * _be_eaten_chesspiece;//被吃的棋子
	void step_clone(Chess_Step * other_step);//

};

#endif