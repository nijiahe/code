#ifndef __Grounds_Select_Layer_H__
#define __Grounds_Select_Layer_H__

#include "Common.h"

USING_NS_CC;


class Grounds_Select_Layer:public Layer
{
public:
	CREATE_FUNC(Grounds_Select_Layer);
	bool init();
	void runtouch();
	bool isclick(Touch* touch);

	void back_menu_callback(Ref * ref);

	int _Rounds_count = 8;
	ScrollView * _view;


};

#endif