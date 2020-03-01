#include "MenuCtl.h"


bool MenuCtl::init()
{
	CCMenu::init();
	schedule(SEL_SCHEDULE(&MenuCtl::schedule_callback));
	return true;
}

void MenuCtl::schedule_callback(float t)
{
	if (this->_selectedItem && this->_state == Menu::State::TRACKING_TOUCH)
	{
		_selectedItem->activate();
	}
}