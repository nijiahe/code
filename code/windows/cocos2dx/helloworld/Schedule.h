#ifndef __Schedule_H_
#define __Schedule_H_

#include"cocos2d.h"
USING_NS_CC;

/*��ʱ��*/
class Schedule :public Layer
{
public:
	CREATE_FUNC(Schedule);//�������Ϊcreate,�����������init
							 //static MyLayer* create();
	bool init();
	static Scene* createscene();//�����������������create
	
	void update(float dt) override;
	void myonecschedule(float dt);

};

#endif
