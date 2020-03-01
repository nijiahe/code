#include "MenuCtl.h"


bool MenuCtl::init()
{
	if (!Menu::init())
	{
		return false;
	}
	
	schedule(SEL_SCHEDULE(&MenuCtl::schedule_callfunc));
	
	return true;
}

void MenuCtl::schedule_callfunc(float t)
{
	if (_state == Menu::State::TRACKING_TOUCH&&_selectedItem)
	{
		_selectedItem->activate();
	}

}
