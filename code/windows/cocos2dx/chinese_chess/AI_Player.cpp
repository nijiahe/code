#include "AI_Player.h"
#include "PLayer.h"
#include "Chesspiece.h"
#include "Chesspiece_Place.h"
#include "Chess_Board.h"
#include "Chess_Step.h"


void AI_Player::make_step()//����һ����С��,ʹ
{
	int highScore = -3000;
	Chess_Step * ret = Chess_Step::create();
	// �������п��ܵ��ƶ�������
	Vector<Chess_Step *> allMove = get_allposible_move();
	for (int i = 0; i < allMove.size(); i++)
	{
		_chess->run_step(allMove.at(i));//��һ����,ת��һ��˭����
		_chess->switch_current_color();
		int score = getMinScore(_AI_IQ,&highScore);//����ʣ���������,��ʱ���ҷ��������ĳ����
		_chess->return_step(allMove.at(i));//��һ����,�����а�����ת��һ��˭����
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

int AI_Player::getMinScore(int remain_IQ, int * curMinScore)//���ֵļ���,������Ҫ�ڵ�ǰ�ľ�����ѡ����������һ��,�����ҷ��ľ�����С,�������ﷵ�ص��ǵ�ǰ�����������һ�����ҷ���������
{
	if (remain_IQ == 0)
	{
		return get_Strength_gap();//���ʣ������Ϊ0,���ش�ʱ�ĳ����
	}
	int minScore = 3000;
	Vector<Chess_Step *> allMove = get_allposible_move();//�õ��Է������п���
	for (int i = 0; i < allMove.size(); i++)
	{
		_chess->run_step(allMove.at(i));//��һ����,ת��һ��˭����
		_chess->switch_current_color();
		int score = getMaxScore(remain_IQ - 1, &minScore);//����ʣ���������,��ʱ���ҷ��������ĳ����
		_chess->return_step(allMove.at(i));//��һ����,�����а�����ת��һ��˭����
		if (score < *curMinScore)//�����ǰ�������Ѿ��б���һ�������ڼ�ֵ�����Ʒ��С��,�ǾͲ��ñ���,���ҷ������������ϸ�������,��Ϊ������ϸ�����,����ֻ��ѡ���ϸ���������ͼ�ֵ����Ʒ,����������ڵĴ�
		{
			minScore = score;//����ֱ����score����������ϸ������͵ķַ��ػ�ȥ,����һ��������ɸѡ�������ֵ������
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
int AI_Player::getMaxScore(int remain_IQ, int * curMaxScore)//�ҷ�����ʱ�����
{
	if (remain_IQ == 0)
	{
		return get_Strength_gap();//���ʣ������Ϊ0,���ش�ʱ�ĳ����
	}
	int maxScore = -3000;
	Vector<Chess_Step *> allMove = get_allposible_move();//�õ��ҷ������п���
	for (int i = 0; i < allMove.size(); i++)
	{
		_chess->run_step(allMove.at(i));//��һ����,ת��һ��˭����
		_chess->switch_current_color();
		int score = getMinScore(remain_IQ - 1, &maxScore);//����ʣ���������,��ʱ���ҷ��������ĳ����
		_chess->return_step(allMove.at(i));//��һ����,�����а�����ת��һ��˭����
		if (score >= *curMaxScore)//�����������ڴ��ڱ��ϸ�������ֵ��ߵĵ���Ʒ���ߵ�,�ǾͲ��ñ���,�ҷ�Ӧ��ѡ����һ������,��Ϊѡ������һ����������Է���õĶ��������һ�������ĺ�,�Է��������������ѡ��һ����õ�
		{
			maxScore = score;//���Ծ���maxScore���浱ǰ�������һ��������ֵ�ߵ�ֵ����,����һ��������ɸѡ��Сֵ������
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
	// ���ݵ�ǰ�췽���Ǻڷ���,���������ƶ��Ĳ�����Ϣ
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

int AI_Player::get_all_chesspiece_vale()//�ҵ�ʵ��
{
	int num = 0;
	for (int i = 0; i < _chess_vector.size(); i++)
	{
		num += chesspiece_value(_chess_vector.at(i));
	}
	return num;
}

int AI_Player::get_board_chesspiece_value()//�ҺͶԷ�ʵ���ܺ�
{
	int num = 0;
	for (int i = 0; i < _chess->_chess_vec.size(); i++)
	{
		num += chesspiece_value(_chess->_chess_vec.at(i));
	}
	return num;
}

int AI_Player::get_Strength_gap()//�ҺͶԷ���ʵ�����
{
	return 2 * get_all_chesspiece_vale() - get_board_chesspiece_value();
}