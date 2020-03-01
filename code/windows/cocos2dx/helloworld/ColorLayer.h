#ifndef __ColorLayer_H_
#define __ColorLayer_H_

#include"cocos2d.h"
USING_NS_CC;

/*多彩图层*/
class ColorLayer:public LayerColor
{
public:
	CREATE_FUNC(ColorLayer);//这个函数为create,调用它会调用init
						 //static MyLayer* create();
	bool init();
	static Scene* createscene();//调用这个函数来调用create
};

#endif
