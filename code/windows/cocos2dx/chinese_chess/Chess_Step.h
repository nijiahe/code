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
	Chesspiece * _move_chesspiece;//���ƶ�������
	Chesspiece_Place _origin_place;//��ʼλ��
	Chesspiece_Place _des_place;//Ŀ��λ��

	Chesspiece * _be_eaten_chesspiece;//���Ե�����
	void step_clone(Chess_Step * other_step);//

};

#endif