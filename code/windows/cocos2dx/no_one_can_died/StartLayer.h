#ifndef __StartLayer_H_
#define __StartLayer_H_

#include "cocos2d.h"
USING_NS_CC;

class StartLayer:public LayerColor
{
public:
	CREATE_FUNC(StartLayer);
	static Scene * createscene();
	bool init();
	enum degree_diffeculty
	{
		normal = 1,
		hard,
		hell,
	};

	void normal_menu_callfunc(Ref * ref);
	void hard_menu_callfunc(Ref * ref);
	void hell_menu_callfunc(Ref * ref);
	void quit_menu_callfunc(Ref * ref);
};
#endif

