#ifndef __Coordinate_H_
#define __Coordinate_H_

#include"cocos2d.h"
USING_NS_CC;

/*������������������*/
class Coordinate :public Layer
{
public:
	CREATE_FUNC(Coordinate);//�������Ϊcreate,�����������init
							   //static MyLayer* create();
	bool init();
	static Scene* createscene();//�����������������create
};

#endif
