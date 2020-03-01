#ifndef __memory_H_
#define __memory_H_

#include"cocos2d.h"
USING_NS_CC;

/*内存管理与内存管理的例外__Array,Menu菜单*/
class memory :public LayerColor
{
public:
	CREATE_FUNC(memory);//这个函数为create,调用它会调用init
						 //static MyLayer* create();
	bool init();
	static Scene* createscene();//调用这个函数来调用create
	
								
	/*
	void myschedule(float dt);
	*/
	enum
	{
		picture1
	};
	__Array* array;
	void menucallback(Ref* ref);
	void onExit() override;
	//void onEnter() override;
};

#endif
