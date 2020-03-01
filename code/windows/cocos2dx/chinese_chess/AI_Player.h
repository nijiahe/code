#ifndef __AI_PLAYER_H__
#define __AI_PLAYER_H__

#include "PLayer.h"

#include "cocos2d.h"
USING_NS_CC;

class Chess_Step;
class Chesspiece;

class AI_Player:public PLayer
{
public:
	int chesspiece_value(Chesspiece * chesspiece);
	int get_all_chesspiece_vale();
	int get_board_chesspiece_value();
	int get_Strength_gap();
	void make_step();
	Vector<Chess_Step *> get_allposible_move();


	
	int getMinScore(int remain_IQ, int * curMinScore);
	int getMaxScore(int remain_IQ, int * curMaxScore);

	int _AI_IQ=1;
};
#endif

