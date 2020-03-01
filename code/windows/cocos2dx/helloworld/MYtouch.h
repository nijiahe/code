#ifndef __MYtouch_H_
#define __MYtouch_H_

#include"cocos2d.h"
USING_NS_CC;

/*触摸控制*/
class MYtouch :public LayerColor
{
public:
	CREATE_FUNC(MYtouch);//这个函数为create,调用它会调用init
						  //static MyLayer* create();
	bool init();
	static Scene* createscene();//调用这个函数来调用create
	void Runtouch();
	enum
	{
		BULLET
	};
};

#endif
