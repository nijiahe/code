#ifndef __diffeculty_select_H__
#define __diffeculty_select_H__

#include "cocos2d.h"
USING_NS_CC;

class diffeculty_select :public LayerColor
{
public:
	CREATE_FUNC(diffeculty_select);
	bool init();
	static Scene* createscene();
	enum
	{
		startmenutag,
		startlabeltag,
		quitmenutag,
		quitlabeltag,
		backlabeltag,
		backmenutag,
	};
	void easyfunc(Ref* ref);
	void hardfunc(Ref* ref);
	void backfunc(Ref* ref);
};
#endif


