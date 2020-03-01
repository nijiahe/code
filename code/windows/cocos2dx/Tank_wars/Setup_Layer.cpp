#include "Setup_Layer.h"
#include "ui/CocosGUI.h"//UI控件头文件的引入
#include "cocos-ext.h"//cocos2dx扩展头文件
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;//SimpleAudioEngine声音文件的命名空间

USING_NS_CC_EXT;

bool Setup_Layer::init()
{
	if (!LayerColor::initWithColor(Color4B(192, 192, 192, 128)))
	{
		return false;
	}

	ControlSlider * _background_slider = ControlSlider::create("UI/sliderTrack.png", "UI/sliderProgress.png", "UI/sliderThumb.png");
	_background_slider->setPosition(Winsize.width*0.5+100, Winsize.height*0.5 - 50);
	_background_slider->setMaximumAllowedValue(1.0f);
	_background_slider->setMinimumAllowedValue(0.0f);
	_background_slider->setMaximumValue(1.0f);//设置最右边的值是多少
	_background_slider->setMinimumValue(0.0f);//设置最左边的值是多少
	float fVolumeBG = UserDefault::getInstance()->getFloatForKey("BGVolume", 0.5f);
	_background_slider->setValue(fVolumeBG);
	_background_slider->addTargetWithActionForControlEvents(this, Control::Handler(&Setup_Layer::set_background_music_volume), Control::EventType::VALUE_CHANGED);
	addChild(_background_slider);
	
	ControlSlider * _effect_slider = ControlSlider::create("UI/sliderTrack.png", "UI/sliderProgress.png", "UI/sliderThumb.png");
	_effect_slider->setPosition(Winsize.width*0.5+100, Winsize.height*0.5+ 50 );
	_effect_slider->setMaximumAllowedValue(1.0f);
	_effect_slider->setMinimumAllowedValue(0.0f);
	_effect_slider->setMaximumValue(1.0f);//设置最右边的值是多少
	_effect_slider->setMinimumValue(0.0f);//设置最左边的值是多少
	float fVolumeEffect = UserDefault::getInstance()->getFloatForKey("EffectVolume", 0.5f);
	_effect_slider->setValue(fVolumeEffect);
	_effect_slider->addTargetWithActionForControlEvents(this, Control::Handler(&Setup_Layer::set_effect_music_volume), Control::EventType::VALUE_CHANGED);
	addChild(_effect_slider);

	Label * tittle_label = Label::createWithTTF("Set", "fonts/arial.ttf", 50); 
	tittle_label->setColor(Color3B::BLACK);
	tittle_label->setPosition(Winsize.width*0.5, Winsize.height*0.8);
	tittle_label->setAnchorPoint(Vec2(0.5, 0.5));
	addChild(tittle_label);

	Label * background_label = Label::createWithTTF("background", "fonts/arial.ttf", 50);
	background_label->setColor(Color3B::BLACK);
	background_label->setPosition(Winsize.width*0.5 + 100 - _background_slider->getContentSize().width-20, Winsize.height*0.5 - 50);
	background_label->setAnchorPoint(Vec2(0.5, 0.5));
	addChild(background_label);

	Label * effect_label = Label::createWithTTF("effect", "fonts/arial.ttf", 50);
	effect_label->setColor(Color3B::BLACK);
	effect_label->setPosition(Winsize.width*0.5 + 100 - _background_slider->getContentSize().width - 20, Winsize.height*0.5 + 50);
	effect_label->setAnchorPoint(Vec2(0.5, 0.5));
	addChild(effect_label);

	EventListenerTouchOneByOne * mylistener = EventListenerTouchOneByOne::create();
	mylistener->onTouchBegan = [=](Touch* touch, Event* event) mutable//指按下时
	{ 
		return true;
	};

	mylistener->onTouchMoved = [=](Touch* touch, Event* event) mutable//指移动时
	{
	};
	mylistener->onTouchEnded = [=](Touch* touch, Event* event) //松开时
	{
	};
	mylistener->setSwallowTouches(true);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(mylistener, this);

	MenuItem * back_item = MenuItemImage::create("paddle/btn_back_normal.png", "paddle/btn_back_press.png", CC_CALLBACK_1(Setup_Layer::close_callback, this));
	back_item->setPosition(0, -Winsize.height*0.3f);
	back_item->setScale(2.5f);
	Menu * back_menu = Menu::create(back_item, NULL);
	
	addChild(back_menu);

	return true;
}

void Setup_Layer::close_callback(Ref * ref)
{
	Director::getInstance()->resume();
	this->removeFromParent();
}

void Setup_Layer::set_background_music_volume(Ref* ref, Control::EventType controlEvents)
{
	ControlSlider* slider = dynamic_cast<ControlSlider*>(ref);
	
	float volume = slider->getValue();
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(volume);
	UserDefault::getInstance()->setFloatForKey("BGVolume", volume);
}

void Setup_Layer::set_effect_music_volume(Ref* ref, Control::EventType controlEvents)
{
	ControlSlider* slider = dynamic_cast<ControlSlider*>(ref);
	float volume = slider->getValue();
	SimpleAudioEngine::getInstance()->setEffectsVolume(slider->getValue());
	UserDefault::getInstance()->setFloatForKey("EffectVolume", volume);
}

