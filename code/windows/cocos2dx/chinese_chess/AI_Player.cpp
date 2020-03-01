#include "AI_Player.h"
#include "PLayer.h"
#include "Chesspiece.h"
#include "Chesspiece_Place.h"
#include "Chess_Board.h"
#include "Chess_Step.h"


void AI_Player::make_step()//定义一个极小分,使
{
	int highScore = -3000;
	Chess_Step * ret = Chess_Step::create();
	// 产生所有可能的移动，遍历
	Vector<Chess_Step *> allMove = get_allposible_move();
	for (int i = 0; i < allMove.size(); i++)
	{
		_chess->run_step(allMove.at(i));//下一步棋,转换一下谁改下
		_chess->switch_current_color();
		int score = getMinScore(_AI_IQ,&highScore);//传入剩余电脑智商,此时对我方最有利的场面分
		_chess->return_step(allMove.at(i));//悔一步棋,在其中包含了转化一下谁该下
		if (score > highScore)
		{
			highScore = score;
			ret = allMove.at(i);
			ret->step_clone(allMove.at(i));
		}
	}
	allMove.clear();
	_current_step = ret;
}

int AI_Player::getMinScore(int remain_IQ, int * curMinScore)//对手的计算,对手需要在当前的局面中选择最有利的一步,及让我方的局面最小,所以这里返回的是当前局面对手在下一步对我方最不利的情况
{
	if (remain_IQ == 0)
	{
		return get_Strength_gap();//如果剩余智商为0,返回此时的场面分
	}
	int minScore = 3000;
	Vector<Chess_Step *> allMove = get_allposible_move();//得到对方的所有可能
	for (int i = 0; i < allMove.size(); i++)
	{
		_chess->run_step(allMove.at(i));//下一步棋,转换一下谁改下
		_chess->switch_current_color();
		int score = getMaxScore(remain_IQ - 1, &minScore);//传入剩余电脑智商,此时对我方最有利的场面分
		_chess->return_step(allMove.at(i));//悔一步棋,在其中包含了转化一下谁该下
		if (score < *curMinScore)//如果当前背包内已经有比上一个背包内价值最低物品更小的,那就不用比了,对我方更有利的是上个背包的,因为如果是上个背包,对手只能选择上个背包内最低价值的物品,比这个背包内的大
		{
			minScore = score;//所以直接让score保存这个比上个背包低的分返回回去,在上一个函数中筛选保留最大值后被遗弃
			break;
		}
		if (score < minScore)
		{
			minScore = score;
		}
	}
	allMove.clear();
	return minScore;
}
int AI_Player::getMaxScore(int remain_IQ, int * curMaxScore)//我方下棋时的情况
{
	if (remain_IQ == 0)
	{
		return get_Strength_gap();//如果剩余智商为0,返回此时的场面分
	}
	int maxScore = -3000;
	Vector<Chess_Step *> allMove = get_allposible_move();//得到我方的所有可能
	for (int i = 0; i < allMove.size(); i++)
	{
		_chess->run_step(allMove.at(i));//下一步棋,转换一下谁改下
		_chess->switch_current_color();
		int score = getMinScore(remain_IQ - 1, &maxScore);//传入剩余电脑智商,此时对我方最有利的场面分
		_chess->return_step(allMove.at(i));//悔一步棋,在其中包含了转化一下谁该下
		if (score >= *curMaxScore)//如果这个背包内存在比上个背包价值最高的的物品更高的,那就不用比了,我方应该选择上一个背包,因为选择了这一个背包代表对方获得的东西会比上一个背包的好,对方会在这个背包内选择一个最好的
		{
			maxScore = score;//所以就让maxScore保存当前这个比上一个背包价值高的值返回,在上一级函数中筛选最小值后遗弃
			break;
		}
		if (score > maxScore)
		{
			maxScore = score;
		}
	}
	allMove.clear();
	return maxScore;
}

Vector<Chess_Step *> AI_Player::get_allposible_move()
{
	Vector<Chess_Step *> step_vec;
	// 根据当前红方还是黑方走,决定可能移动的步骤信息
	if (_chess->_current_color == _chess_color)
	{
		for (int i = 0; i < _chess_vector.size(); i++)
		{
			for (int row = 0; row <= 8; ++row)
			{
				for (int col = 0; col <= 9; ++col)
				{
					if (_chess_vector.at(i)->is_chess_can_moveto(Chesspiece_Place(row, col)))
					{
						Chess_Step * step = Chess_Step::create();
						step->_move_chesspiece = _chess_vector.at(i);
						step->_origin_place = _chess_vector.at(i)->_place;
						if (_chess->is_has_differentcolor_chesspiece(_chess_vector.at(0), Chesspiece_Place(row, col)))
						{
							step->_be_eaten_chesspiece = _chess->find_chesspiece_by_position(Chesspiece_Place(row, col));
						}
						else
						{
							step->_be_eaten_chesspiece = nullptr;
						}
						step->_des_place = Chesspiece_Place(row, col);
						_chess_step_vector.pushBack(step); 
						step_vec.pushBack(step);
					}				
				}
			}
				
		}
	}
	else if (_chess->_current_color == _chess->_me->_chess_color)
	{
		for (int i = 0; i <_chess->_me->_chess_vector.size(); i++)
		{
			for (int row = 0; row <= 8; ++row)
			{
				for (int col = 0; col <= 9; ++col)
				{
					if (_chess->_me->_chess_vector.at(i)->is_chess_can_moveto(Chesspiece_Place(row, col)))
					{
						Chess_Step * step = Chess_Step::create();
						step->_move_chesspiece = _chess->_me->_chess_vector.at(i);
						step->_origin_place = _chess->_me->_chess_vector.at(i)->_place;
						if (_chess->is_has_differentcolor_chesspiece(_chess->_me->_chess_vector.at(0), Chesspiece_Place(row, col)))
						{
							step->_be_eaten_chesspiece = _chess->find_chesspiece_by_position(Chesspiece_Place(row, col));
						}
						else
						{
							step->_be_eaten_chesspiece = nullptr;
						}
						step->_des_place = Chesspiece_Place(row, col);
						_chess->_me->_chess_step_vector.pushBack(step);
						step_vec.pushBack(step);
					}
				}
			}
		}
	}
	return step_vec;
}

int AI_Player::chesspiece_value(Chesspiece * chesspiece)
{
	if (chesspiece->_type == Chesspiece::Chesspiece_Type::che)
	{
		return 100;
	}
	else if (chesspiece->_type == Chesspiece::Chesspiece_Type::ma)
	{
		return 50;
	}
	else if (chesspiece->_type == Chesspiece::Chesspiece_Type::pao)
	{
		return 50;
	}
	else if (chesspiece->_type == Chesspiece::Chesspiece_Type::xiang)
	{
		return 30;
	}
	else if (chesspiece->_type == Chesspiece::Chesspiece_Type::shi)
	{
		return 30;
	}
	else if (chesspiece->_type == Chesspiece::Chesspiece_Type::jiang)
	{
		return 1000;
	}
	else if (chesspiece->_type == Chesspiece::Chesspiece_Type::bing)
	{
		if (_chess->is_has_in_cross(chesspiece))
		{
			return 30;
		}
		else
		{
			return 10;
		}
	}
	else
	{
		return 0;
	}
}

int AI_Player::get_all_chesspiece_vale()//我的实力
{
	int num = 0;
	for (int i = 0; i < _chess_vector.size(); i++)
	{
		num += chesspiece_value(_chess_vector.at(i));
	}
	return num;
}

int AI_Player::get_board_chesspiece_value()//我和对方实力总和
{
	int num = 0;
	for (int i = 0; i < _chess->_chess_vec.size(); i++)
	{
		num += chesspiece_value(_chess->_chess_vec.at(i));
	}
	return num;
}

int AI_Player::get_Strength_gap()//我和对方的实力差距
{
	return 2 * get_all_chesspiece_vale() - get_board_chesspiece_value();
}