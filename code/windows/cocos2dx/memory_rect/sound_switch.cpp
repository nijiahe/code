#include "sound_switch.h"
#include "GameStartLayer.h"
#include "cocos-ext.h"//cocos2dx扩展头文件
#include "SimpleAudioEngine.h"
USING_NS_CC_EXT;
using namespace CocosDenshion;

bool sound_switch::init()
{
	if (!LayerColor::initWithColor(Color4B(105, 105, 105, 180)))
	{
		return false;
	}
	Size visible = Director::getInstance()->getWinSize();

	
	/*backsound_switch菜单*/
	Label* backsound_switch_label = Label::createWithTTF("EASY", "fonts/Marker Felt.ttf", 35);
	backsound_switch_label->enableOutline(Color4B(0, 0, 255, 255), 15);
	backsound_switch_label->enableGlow(Color4B(0, 0, 0, 255));
	backsound_switch_label->setTag(backsound_switch_labeltag);
	MenuItem* backsound_switch_label_menu = MenuItemLabel::create(backsound_switch_label, CC_CALLBACK_1(sound_switch::backsound_switch, this));
	backsound_switch_label_menu->setTag(backsound_switch_menutag);
	backsound_switch_label_menu->setScale(0.6f);
	backsound_switch_label_menu->setColor(Color3B(0, 0, 0));

	/*effect_sound_switch菜单*/
	Label* effect_sound_switch_label = Label::createWithTTF("HARD", "fonts/Marker Felt.ttf", 35);
	effect_sound_switch_label->enableOutline(Color4B(0, 0, 255, 255), 15);
	effect_sound_switch_label->enableGlow(Color4B(0, 0, 0, 255));
	effect_sound_switch_label->setTag(effect_sound_labeltag);
	MenuItem* effect_sound_switch_menu = MenuItemLabel::create(effect_sound_switch_label, CC_CALLBACK_1(sound_switch::effect_sound_switch, this));
	effect_sound_switch_menu->setTag(effect_sound_label_menutag);
	effect_sound_switch_menu->setScale(0.6f);
	effect_sound_switch_menu->setColor(Color3B(0, 0, 0));

	/*back菜单*/
	Label* backlabel = Label::createWithTTF("BACK", "fonts/Marker Felt.ttf", 35);
	backlabel->enableOutline(Color4B(0, 0, 255, 255), 15);
	backlabel->enableGlow(Color4B(0, 0, 0, 255));
	backlabel->setTag(backlabeltag);
	MenuItem* backmenu = MenuItemLabel::create(backlabel, CC_CALLBACK_1(sound_switch::backfunc, this));
	backmenu->setTag(backmenutag);
	backmenu->setScale(0.6f);
	backmenu->setColor(Color3B(0, 0, 0));


	/*设置菜单位置*/
	Menu* menu = Menu::create(backsound_switch_label_menu, effect_sound_switch_menu, backmenu, NULL);
	menu->alignItemsVerticallyWithPadding(visible.height*0.2);
	backsound_switch_label_menu->setPositionY(backsound_switch_label_menu->getPositionY() - 0.1*visible.height);
	effect_sound_switch_menu->setPositionY(effect_sound_switch_menu->getPositionY() - 0.1*visible.height);
	backmenu->setPositionY(backmenu->getPositionY() - 0.1*visible.height);
	addChild(menu);
	return true;


	return true;
}

Scene* sound_switch::createscene()
{
	Scene* scene = Scene::create();
	sound_switch* layer = sound_switch::create();
	scene->addChild(layer);
	return scene;
}

void sound_switch::backsound_switch(Ref* ref)
{
	SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
}
void sound_switch::effect_sound_switch(Ref* ref)
{
	SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
}

void sound_switch::backfunc(Ref* ref)
{
	SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
	GameStartLayer* layer = GameStartLayer::create();
	dynamic_cast<Scene*>(this->getParent())->addChild(layer);
	this->removeFromParent();
}