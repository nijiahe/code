#ifndef __lostlayer_H__
#define __lostlayer_H__

#include "rect.h"
#include "cocos2d.h"
USING_NS_CC;

class lostlayer :public LayerColor
{
public:
	CREATE_FUNC(lostlayer);
	bool init();
	Scene* createscene();
	enum
	{
		bmfonttag,
		tyragain_labeltag,
		tyragain_menutag,
		backtomenu_labeltag,
		backtomenu_menutag,
	};
	void tryagainfunc(Ref* ref);
	void backtomenufunc(Ref* ref);
};
#endif