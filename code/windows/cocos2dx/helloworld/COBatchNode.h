#ifndef __COBatchNode_H_
#define __COBatchNode_H_

#include"cocos2d.h"
USING_NS_CC;

/*游戏优化,创建一个batchnode在scene上,先进行一次渲染*/
class COBatchNode :public Layer
{
public:
	CREATE_FUNC(COBatchNode);//这个函数为create,调用它会调用init
							//static MyLayer* create();
	bool init();
	static Scene* createscene();//调用这个函数来调用create
	
};

#endif
