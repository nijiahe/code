#ifndef __GameStartLayer_H__
#define __GameStartLayer_H__

#include "cocos2d.h"
USING_NS_CC;

class GameStartLayer:public LayerColor
{
public:
	CREATE_FUNC(GameStartLayer);
	bool init();
	static Scene* createscene();
	enum
	{
		title1tag,
		title2tag, 
		startmenutag,
		startlabeltag,
		quitmenutag,
		quitlabeltag,
	};
	void startfunc(Ref* ref);
	void quitfunc(Ref* ref);
};
#endif


