#include "Chesspiece.h"
#include "Chess_Board.h"

bool Chesspiece::init(Chesspiece_Place place, Chesspiece_Type type, Chess_Color _color)
{
	switch (_color._color)
	{
	case Chess_Color::red:
	{
		this->_color = Chess_Color(Chess_Color::red);
		switch (type)
		{
		case che:
			this->_type = che;
			Sprite::initWithFile("rche.png");
			break;
		case ma:
			this->_type = ma;
			Sprite::initWithFile("rma.png");
			break;
		case pao:
			this->_type = pao;
			Sprite::initWithFile("rpao.png");
			break;
		case xiang:
			this->_type = xiang;
			Sprite::initWithFile("rxiang.png");
			break;
		case shi:
			this->_type = shi;
			Sprite::initWithFile("rshi.png");
			break;
		case jiang:
			this->_type = jiang;
			Sprite::initWithFile("rshuai.png");
			break;
		case bing:
			this->_type = bing;
			Sprite::initWithFile("rbing.png");
			break;
		}
	}
	break;
	case Chess_Color::black:
	{
		this->_color = Chess_Color(Chess_Color::black);
		switch (type)
		{
		case che:
			this->_type = che;
			Sprite::initWithFile("bche.png");
			break;
		case ma:
			this->_type = ma;
			Sprite::initWithFile("bma.png");
			break;
		case pao:
			this->_type = pao;
			Sprite::initWithFile("bpao.png");
			break;
		case xiang:
			this->_type = xiang;
			Sprite::initWithFile("bxiang.png");
			break;
		case shi:
			this->_type = shi;
			Sprite::initWithFile("bshi.png");
			break;
		case jiang:
			this->_type = jiang;
			Sprite::initWithFile("bjiang.png");
			break;
		case bing:
			this->_type = bing;
			Sprite::initWithFile("bzu.png");
			break;
		}
		
	}
	break;
	}
	this->_place = place;
	return true;
}

Chesspiece * Chesspiece::create(Chesspiece_Place place, Chesspiece_Type type, Chess_Color color)
{
	Chesspiece * chesspiece = new Chesspiece;
	if (chesspiece&&chesspiece->init(place, type, color))
	{
		chesspiece->autorelease();
	}
	else
	{
		delete chesspiece;
		chesspiece = NULL;
	}
	return chesspiece;
}

bool Chesspiece::is_chess_can_moveto(Chesspiece_Place place)
{

	bool flag = false;
	Chess_Board * board = dynamic_cast<Chess_Board *>(getParent()->getParent());
	if (board == NULL)
	{
		return false;
	}

	switch (this->_type)
	{
	case che:
		if ((this->_place.columns == place.columns || 
			this->_place.lines == place.lines)&&
			!board->is_has_chesspiece_among(this->_place,place)&&
			!board->is_has_samecolor_chesspiece(this, place))
		{
			flag = true;
		}
		break;
	case ma:
		if (place - this->_place == Chesspiece_Place(2,1)
			&&!board->is_has_chesspiece(this,Chesspiece_Place(1,0))&& 
			!board->is_has_samecolor_chesspiece(this, place))
		{
			flag = true;
		}
		else if (place - this->_place == Chesspiece_Place(2, -1)
			&& !board->is_has_chesspiece(this, Chesspiece_Place(1, 0)) &&
			!board->is_has_samecolor_chesspiece(this, place))
		{
			flag = true;
		}
		else if (place - this->_place == Chesspiece_Place(-1, 2)
			&& !board->is_has_chesspiece(this, Chesspiece_Place(0, 1)) &&
			!board->is_has_samecolor_chesspiece(this, place))
		{
			flag = true;
		}
		else if (place - this->_place == Chesspiece_Place(1, 2)
			&& !board->is_has_chesspiece(this, Chesspiece_Place(0, 1)) &&
			!board->is_has_samecolor_chesspiece(this, place))
		{
			flag = true;
		}
		else if (place - this->_place == Chesspiece_Place(-2, 1)
			&& !board->is_has_chesspiece(this, Chesspiece_Place(-1, 0)) &&
			!board->is_has_samecolor_chesspiece(this, place))
		{
			flag = true;
		}
		else if (place - this->_place == Chesspiece_Place(-2, -1)
			&& !board->is_has_chesspiece(this, Chesspiece_Place(-1, 0)) &&
			!board->is_has_samecolor_chesspiece(this, place))
		{
			flag = true;
		}
		else if (place - this->_place == Chesspiece_Place(-1, -2)
			&& !board->is_has_chesspiece(this, Chesspiece_Place(0, -1)) &&
			!board->is_has_samecolor_chesspiece(this, place))
		{
			flag = true;
		}
		else if (place - this->_place == Chesspiece_Place(1, -2)
			&& !board->is_has_chesspiece(this, Chesspiece_Place(0, -1)) &&
			!board->is_has_samecolor_chesspiece(this, place))
		{
			flag = true;
		}
		break;
	case pao:

		if ((this->_place.columns == place.columns || this->_place.lines == place.lines) && !board->is_has_chesspiece_among(this->_place, place) && !board->is_has_chesspiece(place))
		{
			flag = true;
		}
		else if ((this->_place.columns == place.columns || this->_place.lines == place.lines) && board->is_has_onlyone_chesspiece_among(this->_place, place) && board->is_has_differentcolor_chesspiece(this, place))
		{
			flag = true;
		}
		break;
	case xiang:
		if ((place.columns - this->_place.columns == 2 || place.columns - this->_place.columns == -2) &&
			(place.lines - this->_place.lines == 2 || place.lines - this->_place.lines == -2) &&
			!board->is_has_chesspiece((this->_place+place)/2) &&
			!board->is_has_samecolor_chesspiece(this, place)&&
			!board->is_has_cross_river(this,place))
		{
			flag = true;
		}
		break;
	case shi:
		if ((place.columns - this->_place.columns == 1 || place.columns - this->_place.columns == -1) &&
			(place.lines - this->_place.lines == 1 || place.lines - this->_place.lines == -1) &&
			!board->is_has_outof_home(this, place)&&
			!board->is_has_samecolor_chesspiece(this,place))
		{
			flag = true;
		}
		break;
	case jiang:
		if ((place.columns == this->_place.columns && (place.lines - this->_place.lines == 1 || place.lines - this->_place.lines == -1)) ||
			(place.lines == this->_place.lines && (place.columns - this->_place.columns == 1 || place.columns - this->_place.columns == -1)))
		{
			if (!board->is_has_samecolor_chesspiece(this, place)&&!board->is_has_outof_home(this,place))
			{
				flag = true;
			}
		}
		else if (board->get_different_jiang_position(this).columns == this->_place.columns&&!board->is_has_chesspiece_among(this->_place, board->get_different_jiang_position(this))&&place== board->get_different_jiang_position(this)&& board->get_different_jiang_position(this).columns==this->_place.columns)
		{
			flag = true;
		}
		break;
	case bing:
		if (this->_color == Chess_Color(Chess_Color::Holder_Color::red))
		{
			if (place.lines - this->_place.lines == 1 && place.columns - this->_place.columns == 0)
			{
				flag = true;
			}
			else if ((place.columns - this->_place.columns == 1 || place.columns - this->_place.columns == -1) &&
				place.lines - this->_place.lines == 0 &&
				board->is_has_in_cross(this))
			{
				flag = true;
			}
		}
		else if (this->_color == Chess_Color(Chess_Color::Holder_Color::black))
		{
			if (place.lines - this->_place.lines == -1 && place.columns - this->_place.columns == 0)
			{
				flag = true;
			}
			else if ((place.columns - this->_place.columns == 1 || place.columns - this->_place.columns == -1) &&
				place.lines - this->_place.lines == 0 &&
				board->is_has_in_cross(this))
			{
				flag = true;
			}
		}
		break;
	}
	return flag;
}

bool Chesspiece::is_chess_can_moveby(Chesspiece_Place place)
{
	return is_chess_can_moveto(this->_place + place);
}

void Chesspiece::chess_moveto(Chesspiece_Place place)
{
	Chess_Board * board = dynamic_cast<Chess_Board *>(getParent()->getParent());
	if (board == NULL)
	{
		return;
	}
	this->_place = place;
	this->setPosition(board->Converto_Layer_Position(place));
}
void Chesspiece::chess_moveby(Chesspiece_Place place)
{
	return chess_moveto(this->_place + place);
}