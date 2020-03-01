#ifndef __Prepare_Layer_H__
#define __Prepare_Layer_H__

#include "cocos2d.h"
USING_NS_CC;

class Prepare_Layer :public LayerColor
{
public:
	CREATE_FUNC(Prepare_Layer);
	bool init();
	static Scene * createscene();

	void load_resourse();
	void toMainGameLayer();
	void play_action();
	void set_background();
};

#endif