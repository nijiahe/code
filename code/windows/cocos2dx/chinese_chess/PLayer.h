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
	//��Ϸ�߼�
	void start_play(Chess_Board * _chess);
	void add_my_all_chess();//����ҷ�������
	void add_other_all_chess();//��ӶԷ�����

	Chess_Board * _chess;//����
	Chess_Color _chess_color;//��������ɫ
	Chess_Step * _current_step=nullptr;
	Vector<Chesspiece *> _chess_vector;//��������
	Vector<Chesspiece *> _cemetery;//Ĺ��
	Vector<Chess_Step *> _chess_step_vector;
};
#endif

