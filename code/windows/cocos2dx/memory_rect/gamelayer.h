#ifndef __gamelayer_H__
#define __gamelayer_H__

#include "rect.h"
#include "cocos2d.h"
USING_NS_CC;

class gamelayer :public LayerColor
{
public:
	static gamelayer* create(int count);
	bool init(int count);
	std::vector<int> numvec;
	std::vector<rect*> rectvec;
	void putindifferentnum(int count);//将不同的数字放进数组
	void preparerect();//将rect放进数组
	void num_in_rect();
	static Scene* createscene(int count);
	int OKnum = 0;
	int scheduletime = 3;
	int errnonum = 0;
	void showall(float dt);
	void hideall(float dt);
	enum
	{
		atlastag
	};
	void maketimeschedule();
	void timeschedule(float dt);
	void winresolution();
	void lostresolution();
	bool iswin();
	bool islost();
	void closealltouch();
};
#endif