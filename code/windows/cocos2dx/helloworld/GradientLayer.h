#ifndef __GradientLayer_H_
#define __GradientLayerr_H_

#include"cocos2d.h"
USING_NS_CC;

/*����ͼ��*/
class GradientLayer :public LayerGradient
{
public:
	CREATE_FUNC(GradientLayer);//�������Ϊcreate,�����������init
							//static MyLayer* create();
	bool init();
	static Scene* createscene();//�����������������create
};

#endif
