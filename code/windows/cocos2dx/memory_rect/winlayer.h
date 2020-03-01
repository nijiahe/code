#ifndef __winlayer_H__
#define __winlayer_H__

#include "rect.h"
#include "cocos2d.h"
USING_NS_CC;

class winlayer :public LayerColor
{
public:
	CREATE_FUNC(winlayer);
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