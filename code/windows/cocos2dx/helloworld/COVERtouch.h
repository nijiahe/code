#ifndef __COVERtouch_H_
#define __COVERtouch_H_

#include"cocos2d.h"
USING_NS_CC;

/*��������*/
class COVERtouch :public LayerColor
{
public:
	CREATE_FUNC(COVERtouch);//�������Ϊcreate,�����������init
						 //static MyLayer* create();
	bool init();
	void Runtouch();
};

#endif
