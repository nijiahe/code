#ifndef __myLabel_H_
#define __myLabel_H_

#include"cocos2d.h"
USING_NS_CC;

/*Label*/
class myLabel :public LayerColor
{
public:
	CREATE_FUNC(myLabel);//这个函数为create,调用它会调用init
						 //static MyLayer* create();
	bool init();
	static Scene* createscene();//调用这个函数来调用create
	enum Labelstyle
	{
		ttftag,atlastag
	};
	void myschedule(float dt);
};

#endif
