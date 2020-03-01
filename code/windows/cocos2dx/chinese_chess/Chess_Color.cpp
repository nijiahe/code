#include "Chess_Color.h"

Chess_Color::Chess_Color()
{

}

Chess_Color::Chess_Color(Holder_Color color):_color(color)
{

}


bool Chess_Color::operator ==(Chess_Color other)
{
	if (this->_color == other._color)
	{
		return true;
	}
	return false;
}
