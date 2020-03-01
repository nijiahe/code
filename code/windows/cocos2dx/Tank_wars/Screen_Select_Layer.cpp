#include "Screen_Select_Layer.h"
#include "Game_Layer.h"

bool Screen_Select_Layer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	Vector<MenuItem *> item_vec;
	for (int i = 1; i <= 20; ++i)
	{
		MenuItem * item = MenuItemFont::create(Common::format("Round", i));
		item_vec.pushBack(item);
	}

	MenuItemToggle * toogle_item = MenuItemToggle::createWithCallback(CC_CALLBACK_1(Screen_Select_Layer::toogle_callfunc,this), item_vec);
	MenuItem * go_item = MenuItemFont::create("Go", CC_CALLBACK_1(Screen_Select_Layer::go_callfunc, this));
	Menu * menu = Menu::create(toogle_item, go_item, NULL);
	menu->alignItemsVerticallyWithPadding(Winsize.height*0.2);
	addChild(menu);

	return true;
}

void Screen_Select_Layer::toogle_callfunc(Ref * ref)
{
	MenuItemToggle * toogle = (MenuItemToggle *)ref;
	_toogle_index = toogle->getSelectedIndex();
}

void Screen_Select_Layer::go_callfunc(Ref * ref)
{
	Director::getInstance()->replaceScene(Common::createscene(Game_Layer::create(_toogle_index)));
}
