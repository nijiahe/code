#ifndef __background_H__
#define __background_H__

#include "cocos2d.h"
USING_NS_CC;


class background :public LayerColor
{
public:
	CREATE_FUNC(background);
	bool init();
	static Scene* createscene();
	bool sound_switch = false;
	enum
	{
		backgroundspritetag,
		title1tag,
		title2tag,
		sound_switch_tag,
	};
	void sound_control(Ref* ref);
	void changeto_on_picuture();
	void changeto_ban_picuture();
};
#endif