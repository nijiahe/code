#ifndef __COBatchNode_H_
#define __COBatchNode_H_

#include"cocos2d.h"
USING_NS_CC;

/*��Ϸ�Ż�,����һ��batchnode��scene��,�Ƚ���һ����Ⱦ*/
class COBatchNode :public Layer
{
public:
	CREATE_FUNC(COBatchNode);//�������Ϊcreate,�����������init
							//static MyLayer* create();
	bool init();
	static Scene* createscene();//�����������������create
	
};

#endif
