#ifndef __memory_H_
#define __memory_H_

#include"cocos2d.h"
USING_NS_CC;

/*�ڴ�������ڴ���������__Array,Menu�˵�*/
class memory :public LayerColor
{
public:
	CREATE_FUNC(memory);//�������Ϊcreate,�����������init
						 //static MyLayer* create();
	bool init();
	static Scene* createscene();//�����������������create
	
								
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
