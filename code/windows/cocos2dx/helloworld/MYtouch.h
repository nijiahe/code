#ifndef __MYtouch_H_
#define __MYtouch_H_

#include"cocos2d.h"
USING_NS_CC;

/*��������*/
class MYtouch :public LayerColor
{
public:
	CREATE_FUNC(MYtouch);//�������Ϊcreate,�����������init
						  //static MyLayer* create();
	bool init();
	static Scene* createscene();//�����������������create
	void Runtouch();
	enum
	{
		BULLET
	};
};

#endif
