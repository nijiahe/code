#ifndef __Coordinate_H_
#define __Coordinate_H_

#include"cocos2d.h"
USING_NS_CC;

/*本地坐标与世界坐标*/
class Coordinate :public Layer
{
public:
	CREATE_FUNC(Coordinate);//这个函数为create,调用它会调用init
							   //static MyLayer* create();
	bool init();
	static Scene* createscene();//调用这个函数来调用create
};

#endif
