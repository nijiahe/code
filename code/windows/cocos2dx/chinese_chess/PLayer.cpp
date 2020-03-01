#include "PLayer.h"
#include "Chesspiece.h"
#include "Chesspiece_Place.h"
#include "Chess_Board.h"

PLayer::PLayer()
{
	Node::init();
}

void PLayer::add_my_all_chess()
{
	_chess_vector.pushBack(Chesspiece::create(Chesspiece_Place(0, 0), Chesspiece::Chesspiece_Type::che, _chess_color));
	_chess_vector.pushBack(Chesspiece::create(Chesspiece_Place(1, 0), Chesspiece::Chesspiece_Type::ma, _chess_color));
	_chess_vector.pushBack(Chesspiece::create(Chesspiece_Place(2, 0), Chesspiece::Chesspiece_Type::xiang, _chess_color));
	_chess_vector.pushBack(Chesspiece::create(Chesspiece_Place(3, 0), Chesspiece::Chesspiece_Type::shi, _chess_color));
	_chess_vector.pushBack(Chesspiece::create(Chesspiece_Place(4, 0), Chesspiece::Chesspiece_Type::jiang, _chess_color));
	_chess_vector.pushBack(Chesspiece::create(Chesspiece_Place(5, 0), Chesspiece::Chesspiece_Type::shi, _chess_color));
	_chess_vector.pushBack(Chesspiece::create(Chesspiece_Place(6, 0), Chesspiece::Chesspiece_Type::xiang, _chess_color));
	_chess_vector.pushBack(Chesspiece::create(Chesspiece_Place(7, 0), Chesspiece::Chesspiece_Type::ma, _chess_color));
	_chess_vector.pushBack(Chesspiece::create(Chesspiece_Place(8, 0), Chesspiece::Chesspiece_Type::che, _chess_color));
	_chess_vector.pushBack(Chesspiece::create(Chesspiece_Place(1, 2), Chesspiece::Chesspiece_Type::pao, _chess_color));
	_chess_vector.pushBack(Chesspiece::create(Chesspiece_Place(7, 2), Chesspiece::Chesspiece_Type::pao, _chess_color));
	_chess_vector.pushBack(Chesspiece::create(Chesspiece_Place(0, 3), Chesspiece::Chesspiece_Type::bing, _chess_color));
	_chess_vector.pushBack(Chesspiece::create(Chesspiece_Place(2, 3), Chesspiece::Chesspiece_Type::bing, _chess_color));
	_chess_vector.pushBack(Chesspiece::create(Chesspiece_Place(4, 3), Chesspiece::Chesspiece_Type::bing, _chess_color));
	_chess_vector.pushBack(Chesspiece::create(Chesspiece_Place(6, 3), Chesspiece::Chesspiece_Type::bing, _chess_color));
	_chess_vector.pushBack(Chesspiece::create(Chesspiece_Place(8, 3), Chesspiece::Chesspiece_Type::bing, _chess_color));

	for (int i = 0; i < _chess_vector.size(); i++)
	{
		_chess->_background->addChild(_chess_vector.at(i));
		_chess_vector.at(i)->setPosition(_chess->Converto_Layer_Position(_chess_vector.at(i)->_place));
	}
}


void PLayer::add_other_all_chess()
{
	_chess->_other_player->_chess_vector.pushBack(Chesspiece::create(Chesspiece_Place(0, 9), Chesspiece::Chesspiece_Type::che, _chess->_other_player->_chess_color));
	_chess->_other_player->_chess_vector.pushBack(Chesspiece::create(Chesspiece_Place(1, 9), Chesspiece::Chesspiece_Type::ma, _chess->_other_player->_chess_color));
	_chess->_other_player->_chess_vector.pushBack(Chesspiece::create(Chesspiece_Place(2, 9), Chesspiece::Chesspiece_Type::xiang, _chess->_other_player->_chess_color));
	_chess->_other_player->_chess_vector.pushBack(Chesspiece::create(Chesspiece_Place(3, 9), Chesspiece::Chesspiece_Type::shi, _chess->_other_player->_chess_color));
	_chess->_other_player->_chess_vector.pushBack(Chesspiece::create(Chesspiece_Place(4, 9), Chesspiece::Chesspiece_Type::jiang, _chess->_other_player->_chess_color));
	_chess->_other_player->_chess_vector.pushBack(Chesspiece::create(Chesspiece_Place(5, 9), Chesspiece::Chesspiece_Type::shi, _chess->_other_player->_chess_color));
	_chess->_other_player->_chess_vector.pushBack(Chesspiece::create(Chesspiece_Place(6, 9), Chesspiece::Chesspiece_Type::xiang, _chess->_other_player->_chess_color));
	_chess->_other_player->_chess_vector.pushBack(Chesspiece::create(Chesspiece_Place(7, 9), Chesspiece::Chesspiece_Type::ma, _chess->_other_player->_chess_color));
	_chess->_other_player->_chess_vector.pushBack(Chesspiece::create(Chesspiece_Place(8, 9), Chesspiece::Chesspiece_Type::che, _chess->_other_player->_chess_color));
	_chess->_other_player->_chess_vector.pushBack(Chesspiece::create(Chesspiece_Place(1, 7), Chesspiece::Chesspiece_Type::pao, _chess->_other_player->_chess_color));
	_chess->_other_player->_chess_vector.pushBack(Chesspiece::create(Chesspiece_Place(7, 7), Chesspiece::Chesspiece_Type::pao, _chess->_other_player->_chess_color));
	_chess->_other_player->_chess_vector.pushBack(Chesspiece::create(Chesspiece_Place(0, 6), Chesspiece::Chesspiece_Type::bing, _chess->_other_player->_chess_color));
	_chess->_other_player->_chess_vector.pushBack(Chesspiece::create(Chesspiece_Place(2, 6), Chesspiece::Chesspiece_Type::bing, _chess->_other_player->_chess_color));
	_chess->_other_player->_chess_vector.pushBack(Chesspiece::create(Chesspiece_Place(4, 6), Chesspiece::Chesspiece_Type::bing, _chess->_other_player->_chess_color));
	_chess->_other_player->_chess_vector.pushBack(Chesspiece::create(Chesspiece_Place(6, 6), Chesspiece::Chesspiece_Type::bing, _chess->_other_player->_chess_color));
	_chess->_other_player->_chess_vector.pushBack(Chesspiece::create(Chesspiece_Place(8, 6), Chesspiece::Chesspiece_Type::bing, _chess->_other_player->_chess_color));

	for (int i = 0; i < _chess_vector.size(); i++)
	{
		_chess->_background->addChild(_chess_vector.at(i));
		_chess->_other_player->_chess_vector.at(i)->setPosition(_chess->Converto_Layer_Position(_chess->_other_player->_chess_vector.at(i)->_place));
	}
}

