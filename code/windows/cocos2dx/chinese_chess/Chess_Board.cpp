#include "PLayer.h"
#include "People_Player.h"
#include "AI_Player.h"
#include "Chess_Board.h"
#include "Chesspiece_Place.h"
#include "Chesspiece.h"
#include "Chess_Step.h"


bool Chess_Board::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}
	_current_color = Chess_Color(Chess_Color::Holder_Color::red);
	add_chess_board_background();

	monitor_touch();//触摸监听器
	monitor_notice();//通知对方的监听器

	

	return true;
}
Scene * Chess_Board::createscene()
{
	Scene * scene = Scene::create();
	Chess_Board * layer = Chess_Board::create();
	scene->addChild(layer);
	return scene;
}

void Chess_Board::add_chess_board_background()
{
	Size visible = Director::getInstance()->getWinSize();
	_background = Sprite::create("background.png");
	_background->setTag(background_tag);
	_background->setAnchorPoint(Vec2(0, 0));
	addChild(_background);
	_background->setContentSize(Size(1101* visible.height/1101, 1111 * visible.height / 1101));

}

Chesspiece_Place Chess_Board::Converto_Chess_Place(Vec2 position)
{
	Sprite * spr = dynamic_cast<Sprite *>(getChildByTag(background_tag));
	int x_space = spr->getBoundingBox().size.width*0.1;
	int y_space = spr->getBoundingBox().size.height*0.1;
	int x_origin = spr->getBoundingBox().size.width*0.1;
	int y_origin = spr->getBoundingBox().size.height*0.05;

	Chesspiece_Place place;
	for (int i = 0; i < 9; i++)
	{
		if (position.x > x_origin*0.5 + i * x_space&&
			position.x < x_origin*0.5 + (i + 1)*x_space)
		{
			place.columns = i;
		}
	}
	for (int j = 0; j < 10; j++)
	{
		if (position.y > y_origin*0.5 + j * y_space&&
			position.y < y_origin*0.5 + (j + 1)*y_space)
		{
			place.lines = j;
		}
	}
	return place;
}
Vec2 Chess_Board::Converto_Layer_Position(Chesspiece_Place position)
{
	Sprite * spr = dynamic_cast<Sprite *>(getChildByTag(background_tag));
	int x_space = spr->getBoundingBox().size.width*0.1;
	int y_space = spr->getBoundingBox().size.height*0.1;
	int x_origin = spr->getBoundingBox().size.width*0.1;
	int y_origin = spr->getBoundingBox().size.height*0.05;

	return Vec2(x_origin+position.columns*x_space, y_origin+position.lines*y_space);
}


void Chess_Board::draw_chessboard_test()
{
	Size visible = Director::getInstance()->getWinSize();
	Sprite * spr = dynamic_cast<Sprite *>(getChildByTag(background_tag));
	DrawNode * drawnode = DrawNode::create();
	int x_space = spr->getBoundingBox().size.width*0.1;
	int y_space = spr->getBoundingBox().size.height*0.1;
	int x_origin = spr->getBoundingBox().size.width*0.1;
	int y_origin = spr->getBoundingBox().size.height*0.05;
	drawnode->drawLine(Vec2(x_origin, 0), Vec2(x_origin, visible.height), Color4F(Color4B(125, 125, 0, 255)));
	drawnode->drawLine(Vec2(x_origin+1* x_space, 0), Vec2(x_origin + 1 * x_space, visible.height), Color4F(Color4B(125, 125, 0, 255)));
	drawnode->drawLine(Vec2(x_origin+2* x_space, 0), Vec2(x_origin + 2 * x_space, visible.height), Color4F(Color4B(125, 125, 0, 255)));
	drawnode->drawLine(Vec2(x_origin + 8 * x_space, 0), Vec2(x_origin + 8 * x_space, visible.height), Color4F(Color4B(125, 125, 0, 255)));
	drawnode->drawLine(Vec2(0, y_origin), Vec2(visible.width, y_origin), Color4F(Color4B(125, 125, 0, 255)));
	drawnode->drawLine(Vec2(0, y_origin+9* y_space), Vec2(visible.width, y_origin + 9 * y_space), Color4F(Color4B(125, 125, 0, 255)));
	addChild(drawnode);
}

void Chess_Board::runtouch()
{
	Size visible = Director::getInstance()->getWinSize();
	Sprite * spr = dynamic_cast<Sprite *>(getChildByTag(background_tag));
	DrawNode * drawnode = DrawNode::create();
	int x_space = spr->getBoundingBox().size.width*0.1;
	int y_space = spr->getBoundingBox().size.height*0.1;
	int x_origin = spr->getBoundingBox().size.width*0.1;
	int y_origin = spr->getBoundingBox().size.height*0.05;

	if (mylistener == nullptr)
	{
		mylistener = EventListenerTouchOneByOne::create();//创建一个触摸监听
		Rect rect = Rect(0, 0, visible.width, visible.height);//设置触摸区域
		mylistener->setSwallowTouches(true);//设置是否吞噬触摸
		mylistener->onTouchBegan = [=](Touch* touch, Event* event) mutable//指按下时
		{
			return true;
		};

		mylistener->onTouchMoved = [=](Touch* touch, Event* event) mutable//指移动时
		{

		};
		mylistener->onTouchEnded = [=](Touch* touch, Event* event) //松开时
		{
			Vec2 point = touch->getLocation();
			if (point.x>x_origin*0.5&&point.x<spr->getBoundingBox().size.width - x_origin * 0.5&&
				point.y>y_origin*0.5&&point.y<spr->getBoundingBox().size.height - y_origin * 0.5)
			{
				Chesspiece_Place place = Converto_Chess_Place(point);
				if (_select_chesspiece == nullptr)
				{
					if (is_has_samecolor_chesspiece(_me->_chess_vector.at(0), place))
					{
						_select_chesspiece = find_chesspiece_by_position(place);
						add_select_picture(_select_chesspiece);
					}
				}
				else
				{
					if (is_has_samecolor_chesspiece(_me->_chess_vector.at(0), place))
					{
						_select_chesspiece = find_chesspiece_by_position(place);
						add_select_picture(_select_chesspiece);
					}
					else if (_select_chesspiece->is_chess_can_moveto(place))
					{
						dynamic_cast<People_Player *>(_me)->make_step(_select_chesspiece, place);
						_select_chesspiece = nullptr;
					}
					else
					{
						_select_chesspiece = nullptr;
						_select_picture->setVisible(false);
					}
				}

			}
		};

		this->_eventDispatcher->addEventListenerWithSceneGraphPriority(mylistener, this);
	}
}

void Chess_Board::closetouch()
{
	_eventDispatcher->removeEventListener(mylistener);
	mylistener = nullptr;
}

void Chess_Board::monitor_touch()
{
	schedule(SEL_SCHEDULE(&Chess_Board::monitor_touch_callback));
}
void Chess_Board::monitor_touch_callback(float t)
{
	if (_current_color == _me->_chess_color)
	{
		runtouch();

		Chess_Step * step = get_current_step_and_clean(_me);
		if (step != nullptr)
		{
			run_step(step);
			switch_current_color();
			closetouch();
			is_notice = false;
		}
	}
	else
	{
		Chess_Step * step = get_current_step_and_clean(_other_player);
		if (step != nullptr)
		{
			run_step(step);
			switch_current_color();
		}
	}
}

Chess_Step * Chess_Board::get_current_step_and_clean(PLayer * player)
{
	if (player->_current_step!=nullptr)
	{
		player->_chess_step_vector.pushBack(player->_current_step);
		player->_current_step = nullptr;
		return player->_chess_step_vector.at(player->_chess_step_vector.size() - 1);
	}
	else
	{
		return nullptr;
	}
}

void Chess_Board::run_step(Chess_Step * step)
{
	add_red_select_picture(step -> _move_chesspiece);
	if (step->_be_eaten_chesspiece != nullptr)
	{
		Chesspiece * chesspiece = find_chesspiece_by_position(step->_des_place);
		chesspiece->setVisible(false);
		_chess_vec.eraseObject(chesspiece);
		if (step->_move_chesspiece->_color == _me->_chess_color)//我下
		{
			_other_player->_cemetery.pushBack(chesspiece);
			_other_player->_chess_vector.eraseObject(chesspiece);
		}
		else
		{
			_me->_cemetery.pushBack(chesspiece);
			_me->_chess_vector.eraseObject(chesspiece);
		}
		if (step->_be_eaten_chesspiece->_type == Chesspiece::Chesspiece_Type::jiang)//将被吃
		{
			if (step->_be_eaten_chesspiece->_color == _me->_chess_color)//我输了
			{
				Director::getInstance()->pause();
			}
			else if (step->_be_eaten_chesspiece->_color == _me->_chess_color)//我赢了
			{
				Director::getInstance()->pause();
			}
		}
	}
	step->_move_chesspiece->chess_moveto(step->_des_place);
	add_select_picture(step->_move_chesspiece);
}

void Chess_Board::monitor_notice()
{
	schedule(SEL_SCHEDULE(&Chess_Board::notice_other_player));
}

void Chess_Board::notice_other_player(float t)
{
	if (!is_notice&&_current_color == _other_player->_chess_color)//如果还没有通知该对方下且现在应该对方下
	{
		if (_player_type == player_type::AI)//如果对手是AI
		{
			(dynamic_cast<AI_Player *>(_other_player))->make_step();
		}
		else if (_player_type == player_type::People)
		{

		}
		is_notice = true;
	}
	
}

void Chess_Board::regret(int num)
{
	for (int i = 0; i < num; i++)
	{
		if (_current_color == _me->_chess_color)
		{
			return_step(_me->_chess_step_vector.at(_me->_chess_step_vector.size() - 1));
		}
		else if(_current_color == _other_player->_chess_color)
		{
			return_step(_other_player->_chess_step_vector.at(_other_player->_chess_step_vector.size() - 1));
		}
	}
}

void Chess_Board::return_step(Chess_Step * step)
{
	step->_move_chesspiece->chess_moveto(step->_origin_place);
	if (step->_be_eaten_chesspiece != nullptr)
	{
		if (step->_be_eaten_chesspiece->_color == _me->_chess_color)
		{
			_me->_chess_vector.pushBack(step->_be_eaten_chesspiece);
			_me->_chess_step_vector.eraseObject(step);
			this->_chess_vec.pushBack(step->_be_eaten_chesspiece);
			_me->_cemetery.eraseObject(step->_be_eaten_chesspiece);
		}
		else if (step->_be_eaten_chesspiece->_color == _other_player->_chess_color)
		{
			_other_player->_chess_vector.pushBack(step->_be_eaten_chesspiece);
			_other_player->_chess_step_vector.eraseObject(step);
			this->_chess_vec.pushBack(step->_be_eaten_chesspiece);
			_other_player->_cemetery.eraseObject(step->_be_eaten_chesspiece);
		}
		step->_be_eaten_chesspiece->setVisible(true);
	}
	this->switch_current_color();
}



bool Chess_Board::is_has_chesspiece(Chesspiece_Place position)
{

	for (int i = 0; i < _chess_vec.size(); i++)
	{
		if (_chess_vec.at(i)->_place == position)
		{
			return true;
		}

	}

	return false;
}
bool Chess_Board::is_has_red_chesspiece(Chesspiece_Place position)
{
	for (int i = 0; i < _chess_vec.size(); i++)
	{
		if (_chess_vec.at(i)->_place == position&& _chess_vec.at(i)->_color== Chess_Color(Chess_Color::Holder_Color::red))
		{
			return true;
		}
	}
	return false;
}
bool Chess_Board::is_has_black_chesspiece(Chesspiece_Place position)
{
	for (int i = 0; i < _chess_vec.size(); i++)
	{
		if (_chess_vec.at(i)->_place == position && _chess_vec.at(i)->_color == Chess_Color(Chess_Color::Holder_Color::black))
		{
			return true;
		}
	}
	return false;
}

bool Chess_Board::is_has_samecolor_chesspiece(Chesspiece * chess, Chesspiece_Place position)
{
	if (chess->_color == Chess_Color(Chess_Color::Holder_Color::red))
	{
		return is_has_red_chesspiece(position);
	}
	else if (chess->_color == Chess_Color(Chess_Color::Holder_Color::black))
	{
		return is_has_black_chesspiece(position);
	}
	else
	{
		return false;
	}
}

bool Chess_Board::is_has_differentcolor_chesspiece(Chesspiece * chess, Chesspiece_Place position)
{
	if (!is_has_samecolor_chesspiece(chess, position) && is_has_chesspiece(position))
	{
		return true;
	}
	return false;
}

bool Chess_Board::is_has_chesspiece_among(Chesspiece_Place origin_position, Chesspiece_Place des_position)
{
	if (origin_position.columns == des_position.columns)
	{
		for (int i = 0; i < _chess_vec.size(); i++)
		{
			if (((_chess_vec.at(i)->_place.lines > origin_position.lines&&_chess_vec.at(i)->_place.lines < des_position.lines) ||
				(_chess_vec.at(i)->_place.lines<origin_position.lines&&_chess_vec.at(i)->_place.lines>des_position.lines))&&
				_chess_vec.at(i)->_place.columns== origin_position.columns)
			{
				return true;
			}
		}
	}
	else if (origin_position.lines == des_position.lines)
	{
		for (int i = 0; i < _chess_vec.size(); i++)
		{
			if (((_chess_vec.at(i)->_place.columns > origin_position.columns&&_chess_vec.at(i)->_place.columns < des_position.columns) ||
				(_chess_vec.at(i)->_place.columns<origin_position.columns&&_chess_vec.at(i)->_place.columns>des_position.columns))&&
				_chess_vec.at(i)->_place.lines == origin_position.lines)
			{
				return true;
			}
		}
	}
	return false;
}

bool Chess_Board::is_has_onlyone_chesspiece_among(Chesspiece_Place origin_position, Chesspiece_Place des_position)
{
	
	int num = 0;
	if (origin_position.columns == des_position.columns)
	{
		for (int i = 0; i < _chess_vec.size(); i++)
		{
			if (((_chess_vec.at(i)->_place.lines > origin_position.lines&&_chess_vec.at(i)->_place.lines < des_position.lines) ||
				(_chess_vec.at(i)->_place.lines<origin_position.lines&&_chess_vec.at(i)->_place.lines>des_position.lines))&&
				_chess_vec.at(i)->_place.columns== origin_position.columns)
			{
				num++;
			}
		}
	}
	else if (origin_position.lines == des_position.lines)
	{
		for (int i = 0; i < _chess_vec.size(); i++)
		{
			if (((_chess_vec.at(i)->_place.columns > origin_position.columns&&_chess_vec.at(i)->_place.columns < des_position.columns) ||
				(_chess_vec.at(i)->_place.columns<origin_position.columns&&_chess_vec.at(i)->_place.columns>des_position.columns))&&
				_chess_vec.at(i)->_place.lines== origin_position.lines)
			{
				num++;
			}
		}
	}
	else
	{
		return false;
	}

	if (num == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Chess_Board::is_has_cross_river(Chesspiece * chess, Chesspiece_Place position)
{
	if (chess->_color == _me->_chess_color&&position.lines>=5)
	{
		return true;
	}
	else if (chess->_color == _other_player->_chess_color&& position.lines <= 4)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Chess_Board::is_has_outof_home(Chesspiece * chess, Chesspiece_Place position)
{
	if (chess->_color == Chess_Color(Chess_Color::Holder_Color::red) && position.lines <=2&&position.columns >=3&&position.columns <=5)
	{
		return false;
	}
	else if (chess->_color == Chess_Color(Chess_Color::Holder_Color::black) && position.lines >=7 && position.columns >= 3 && position.columns <=5 )
	{
		return false;
	}
	else
	{
		return true;
	}
}

Chesspiece_Place Chess_Board::get_different_jiang_position(Chesspiece * chess)
{
	if (chess->_color == Chess_Color(Chess_Color::Holder_Color::red))
	{
		for (int i = 0; i < _chess_vec.size(); i++)
		{
			if (_chess_vec.at(i)->_type == Chesspiece::Chesspiece_Type::jiang&&_chess_vec.at(i)->_color == Chess_Color(Chess_Color::Holder_Color::black))
			{
				return _chess_vec.at(i)->_place;
			}
		}
	}
	else if (chess->_color == Chess_Color(Chess_Color::Holder_Color::black))
	{
		for (int i = 0; i < _chess_vec.size(); i++)
		{
			if (_chess_vec.at(i)->_type == Chesspiece::Chesspiece_Type::jiang&&_chess_vec.at(i)->_color == Chess_Color(Chess_Color::Holder_Color::red))
			{
				return _chess_vec.at(i)->_place;
			}
		}
	}

	return Chesspiece_Place(0, 0);
}


bool Chess_Board::is_has_chesspiece(Chesspiece * chess, Chesspiece_Place position_by)
{
	return is_has_chesspiece(Chesspiece_Place(chess->_place.columns + position_by.columns, chess->_place.lines + position_by.lines));
}
bool Chess_Board::is_has_red_chesspiece(Chesspiece * chess, Chesspiece_Place position_by)
{
	return is_has_red_chesspiece(Chesspiece_Place(chess->_place.columns + position_by.columns, chess->_place.lines + position_by.lines));
}
bool Chess_Board::is_has_black_chesspiece(Chesspiece * chess, Chesspiece_Place position_by)
{
	return is_has_black_chesspiece(Chesspiece_Place(chess->_place.columns + position_by.columns, chess->_place.lines + position_by.lines));
}
bool Chess_Board::is_has_samecolor_chesspiece_by(Chesspiece * chess, Chesspiece_Place position_by)
{
	if (chess->_color == Chess_Color(Chess_Color::Holder_Color::red))
	{
		return is_has_red_chesspiece(chess, position_by);
	}
	else if (chess->_color == Chess_Color(Chess_Color::Holder_Color::black))
	{
		return is_has_black_chesspiece(chess, position_by);
	}
	else
	{
		return false;
	}
}
bool Chess_Board::is_has_differentcolor_chesspiece_by(Chesspiece * chess, Chesspiece_Place position_by)
{
	if (!is_has_samecolor_chesspiece_by(chess, position_by) && is_has_chesspiece(chess, position_by))
	{
		return true;
	}
	return false;
}
bool Chess_Board::is_has_chesspiece_among(Chesspiece * origin_chess, Chesspiece * des_chess)
{
	return is_has_chesspiece_among(origin_chess->_place, des_chess->_place);
}
bool Chess_Board::is_has_onlyone_chesspiece_among(Chesspiece * origin_chess, Chesspiece * des_chess)
{
	return is_has_chesspiece_among(origin_chess->_place, des_chess->_place);
}
bool Chess_Board::is_has_cross_river_by(Chesspiece * chess, Chesspiece_Place position_by)
{
	return is_has_cross_river(chess, chess->_place + position_by);
}
bool Chess_Board::is_has_outof_home_by(Chesspiece * chess, Chesspiece_Place position_by)
{
	return is_has_outof_home(chess, chess->_place + position_by);
}
Chesspiece_Place Chess_Board::get_different_jiang_position_by(Chesspiece * chess)
{
	return Chesspiece_Place(get_different_jiang_position(chess) - chess->_place);
}
bool Chess_Board::is_has_in_cross(Chesspiece * chess)
{
	if (chess->_color == _me->_chess_color&&chess->_place.lines>=5)
	{
		return true;
	}
	else if (chess->_color == _other_player->_chess_color&&chess->_place.lines<=4)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Chess_Board::switch_current_color()
{
	if (_current_color == Chess_Color(Chess_Color::Holder_Color::red))
	{
		_current_color = Chess_Color(Chess_Color::Holder_Color::black);
	}
	else if (_current_color == Chess_Color(Chess_Color::Holder_Color::black))
	{
		_current_color = Chess_Color(Chess_Color::Holder_Color::red);
	}
}

Chesspiece * Chess_Board::find_chesspiece_by_position(Chesspiece_Place position)
{
	for (int i = 0; i < _chess_vec.size(); i++)
	{
		if (_chess_vec.at(i)->_place == position)
		{
			return _chess_vec.at(i);
		}
	}
	return nullptr;
}

void Chess_Board::add_select_picture(Chesspiece * select_chesspiece)
{
	if (_select_picture == nullptr)
	{
		_select_picture = Sprite::create("selected.png");
		_select_picture->setAnchorPoint(Vec2(0.5, 0.5));
		_select_picture->setPosition(Converto_Layer_Position(select_chesspiece->_place));
		addChild(_select_picture);
	}
	else
	{
		_select_picture->setVisible(true);
		_select_picture->setPosition(Converto_Layer_Position(select_chesspiece->_place));
	}
}

void Chess_Board::add_red_select_picture(Chesspiece * select_chesspiece)
{
	if (_red_select_picture == nullptr)
	{
		_red_select_picture = Sprite::create("red_selected.png");
		_red_select_picture->setAnchorPoint(Vec2(0.5, 0.5));
		_red_select_picture->setPosition(Converto_Layer_Position(select_chesspiece->_place));
		addChild(_red_select_picture);
	}
	else
	{
		_red_select_picture->setVisible(true);
		_red_select_picture->setPosition(Converto_Layer_Position(select_chesspiece->_place));
	}
}