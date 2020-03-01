#ifndef __plant_vs_zombie_Layer_cpp_
#define __plant_vs_zombie_Layer_cpp_

#include"cocos2d.h"
USING_NS_CC;

class plant_vs_zombie_Layer:public Layer
{
public:
	static Scene* createscene();
	static plant_vs_zombie_Layer* create();
	bool init();


};

#endif

