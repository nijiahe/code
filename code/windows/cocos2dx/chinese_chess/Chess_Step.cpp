#include "Chess_Step.h"

bool Chess_Step::init()
{
	return true;
}

void Chess_Step::step_clone(Chess_Step * other_step)
{
	this->_move_chesspiece = other_step->_move_chesspiece;
	this->_origin_place = other_step->_origin_place;
	this->_des_place = other_step->_des_place;
	this->_be_eaten_chesspiece = other_step->_be_eaten_chesspiece;
}