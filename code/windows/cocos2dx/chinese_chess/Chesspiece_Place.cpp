#include "Chesspiece_Place.h"

Chesspiece_Place::Chesspiece_Place(int x, int y):columns(x), lines(y)
{

}

Chesspiece_Place::Chesspiece_Place()
{

}

bool Chesspiece_Place::operator ==(Chesspiece_Place other)
{
	if (this->columns == other.columns&&this->lines == other.lines)
	{
		return true;
	}

	return false;
}

Chesspiece_Place Chesspiece_Place::operator +(Chesspiece_Place other)
{
	return Chesspiece_Place(this->columns + other.columns, this->lines + other.lines);
}

Chesspiece_Place Chesspiece_Place::operator -(Chesspiece_Place other)
{
	return Chesspiece_Place(this->columns - other.columns, this->lines - other.lines);
}
Chesspiece_Place Chesspiece_Place::operator /(int num)
{
	return Chesspiece_Place(this->columns/num, this->lines/num);
}