#ifndef __ColorLayer_H_
#define __ColorLayer_H_

#include"cocos2d.h"
USING_NS_CC;

/*���ͼ��*/
class ColorLayer:public LayerColor
{
public:
	CREATE_FUNC(ColorLayer);//�������Ϊcreate,�����������init
						 //static MyLayer* create();
	bool init();
	static Scene* createscene();//�����������������create
};

#endif
