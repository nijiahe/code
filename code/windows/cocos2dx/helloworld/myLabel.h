#ifndef __myLabel_H_
#define __myLabel_H_

#include"cocos2d.h"
USING_NS_CC;

/*Label*/
class myLabel :public LayerColor
{
public:
	CREATE_FUNC(myLabel);//�������Ϊcreate,�����������init
						 //static MyLayer* create();
	bool init();
	static Scene* createscene();//�����������������create
	enum Labelstyle
	{
		ttftag,atlastag
	};
	void myschedule(float dt);
};

#endif
