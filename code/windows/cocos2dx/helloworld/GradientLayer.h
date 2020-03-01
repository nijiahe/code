#ifndef __GradientLayer_H_
#define __GradientLayerr_H_

#include"cocos2d.h"
USING_NS_CC;

/*渐变图层*/
class GradientLayer :public LayerGradient
{
public:
	CREATE_FUNC(GradientLayer);//这个函数为create,调用它会调用init
							//static MyLayer* create();
	bool init();
	static Scene* createscene();//调用这个函数来调用create
};

#endif
