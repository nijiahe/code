#ifndef __Chesspiece_H__
#define __Chesspiece_H__

#include "cocos2d.h"
USING_NS_CC;

#include "Chesspiece_Place.h"
#include "Chess_Color.h"

class Chesspiece_Place;

class Chesspiece:public Sprite
{
public:
	enum Chesspiece_Type
	{
		che,
		ma,
		pao,
		xiang,
		shi,
		jiang,
		bing,
	};

	bool init(Chesspiece_Place place, Chesspiece_Type type, Chess_Color _color);
	static Chesspiece * create(Chesspiece_Place place, Chesspiece_Type type, Chess_Color color);
	bool is_chess_can_moveto(Chesspiece_Place place);
	bool is_chess_can_moveby(Chesspiece_Place place);
	void chess_moveto(Chesspiece_Place place);
	void chess_moveby(Chesspiece_Place place);

	Chesspiece_Place _place;
	Chesspiece_Type _type;
	Chess_Color _color;
	bool is_in_cemetery;
};
#endif

