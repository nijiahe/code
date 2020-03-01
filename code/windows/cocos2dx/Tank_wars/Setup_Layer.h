#ifndef __Setup_Layer_H__
#define __Setup_Layer_H__


#include "Common.h"
#include "cocos-ext.h"//cocos2dx扩展头文件
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;//SimpleAudioEngine声音文件的命名空间

class MyControlSlider;

USING_NS_CC_EXT;

class Setup_Layer:public LayerColor
{
public:
	bool init();
	CREATE_FUNC(Setup_Layer);

	void set_background_music_volume(Ref* ref, Control::EventType controlEvents);
	void set_effect_music_volume(Ref* ref, Control::EventType controlEvents);
	void close_callback(Ref * ref);
	

	

};

#endif