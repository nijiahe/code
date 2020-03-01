#ifndef __COVERtouch_H_
#define __COVERtouch_H_

#include"cocos2d.h"
USING_NS_CC;

/*触摸控制*/
class COVERtouch :public LayerColor
{
public:
	CREATE_FUNC(COVERtouch);//这个函数为create,调用它会调用init
						 //static MyLayer* create();
	bool init();
	void Runtouch();
};

#endif
