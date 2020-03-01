#ifndef __sound_switch_H__
#define __sound_switch_H__

#include "cocos2d.h"
USING_NS_CC;

class sound_switch :public LayerColor
{
public:
	CREATE_FUNC(sound_switch);
	bool init();
	Scene* createscene();
	enum
	{
		backsound_switch_labeltag,
		backsound_switch_menutag,
		effect_sound_labeltag,
		effect_sound_label_menutag,
		backlabeltag,
		backmenutag,
	};
	void backsound_switch(Ref* ref);
	void effect_sound_switch(Ref* ref);
	void backfunc(Ref* ref);
};
#endif