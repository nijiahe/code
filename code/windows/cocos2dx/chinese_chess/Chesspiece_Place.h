#ifndef __Chesspiece_Place_H__
#define __Chesspiece_Place_H__

class Chesspiece_Place
{
public:
	Chesspiece_Place(int x, int y);
	Chesspiece_Place();
	int lines;
	int columns;

	bool operator ==(Chesspiece_Place other);
	Chesspiece_Place operator +(Chesspiece_Place other);
	Chesspiece_Place operator -(Chesspiece_Place other);
	Chesspiece_Place operator /(int num);
};

#endif