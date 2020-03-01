#include "Chess_Board.h"
#include "People_Player.h"
#include "Player.h"
#include "AI_Player.h"
#include "Start_Game_Layer.h"
#include "Chesspiece.h"
#include "Chess_Step.h"
#include <WinSock2.h>


bool Start_Game_Layer::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}
	srand(time(NULL));
	add_background();
	add_menu();

	return true;
}
Scene * Start_Game_Layer::createscene()
{
	Scene * scene = Scene::create();
	Start_Game_Layer * layer = Start_Game_Layer::create();
	scene->addChild(layer);
	return scene;
}
void Start_Game_Layer::add_background()
{
	Size visible = Director::getInstance()->getWinSize();
	Sprite * chess_board = Sprite::create("background.png");
	chess_board->setAnchorPoint(Vec2(0, 0));
	chess_board->setPosition(0, 0);
	addChild(chess_board);
	chess_board->setContentSize(Size(visible.height, visible.height));

	Sprite * control_board = Sprite::create("floor.jpg");
	control_board->setAnchorPoint(Vec2(0, 0));
	control_board->setPosition(visible.height, 0);
	addChild(control_board);
	control_board->setContentSize(Size(visible.width - visible.height, visible.height));
}
void Start_Game_Layer::add_menu()
{
	Size visible = Director::getInstance()->getWinSize();
	Sprite * play_with_ai_spr = Sprite::create("renjiduizhan.png");
	play_with_ai_spr->setAnchorPoint(Vec2(0.5, 0.5));
	Sprite * play_with_ai_spr_press = Sprite::create("renjiduizhan_press.png");
	play_with_ai_spr->setAnchorPoint(Vec2(0.5, 0.5));
	
	Sprite * play_with_player_spr = Sprite::create("lianjiduizhan.png");
	play_with_player_spr->setAnchorPoint(Vec2(0.5, 0.5));
	Sprite * play_with_player_spr_press = Sprite::create("lianjiduizhan_press.png");
	play_with_player_spr_press->setAnchorPoint(Vec2(0.5, 0.5));

	Sprite * quit_spr = Sprite::create("tuichu.png");
	quit_spr->setAnchorPoint(Vec2(0.5, 0.5));
	Sprite * quit_spr_press = Sprite::create("tuichu_press.png");
	quit_spr_press->setAnchorPoint(Vec2(0.5, 0.5));

	MenuItem * renjiduizhan_item = MenuItemSprite::create(play_with_ai_spr, play_with_ai_spr_press, CC_CALLBACK_1(Start_Game_Layer::play_with_ai_menu_callfunc, this));
	renjiduizhan_item->setScale(1.5);
	MenuItem * playerduizhan_item = MenuItemSprite::create(play_with_player_spr, play_with_player_spr_press, CC_CALLBACK_1(Start_Game_Layer::paly_with_player_menu_callfunc, this));
	playerduizhan_item->setScale(1.5);
	MenuItem * quit_item = MenuItemSprite::create(quit_spr, quit_spr_press, CC_CALLBACK_1(Start_Game_Layer::quit_menu_callfunc, this));
	quit_item->setScale(1.5);
	Menu * menu = Menu::create(renjiduizhan_item, playerduizhan_item, quit_item, NULL);
	menu->alignItemsVerticallyWithPadding(visible.height*0.15);
	addChild(menu);
	menu->setPositionX(visible.height + (visible.width - visible.height)*0.5);
}
void Start_Game_Layer::play_with_ai_menu_callfunc(Ref * ref)
{
	Chess_Board * board = Chess_Board::create();
	board->_player_type = Chess_Board::player_type::AI;
	People_Player * player = new People_Player;
	AI_Player * ai = new AI_Player;
	player->_chess = board;
	ai->_chess = board;
	board->_me = (PLayer*)player;
	board->_other_player = (PLayer*)ai;

	Scene * scene = Scene::create();
	scene->addChild(board);
	Director::getInstance()->replaceScene(scene);

	int num = rand() % 2;
	num = 0;
	if (num == 0)
	{
		player->_chess_color = Chess_Color(Chess_Color::Holder_Color::red);
		ai->_chess_color = Chess_Color(Chess_Color::Holder_Color::black);
		player->add_my_all_chess();
		ai->add_other_all_chess();
	}

	else if (num == 1)
	{
		player->_chess_color = Chess_Color(Chess_Color::Holder_Color::black);
		ai->_chess_color = Chess_Color(Chess_Color::Holder_Color::red);
		player->add_my_all_chess();
		ai->add_other_all_chess();
	}
	board->_chess_vec.pushBack(player->_chess_vector);
	board->_chess_vec.pushBack(ai->_chess_vector);
}
void Start_Game_Layer::paly_with_player_menu_callfunc(Ref * ref)
{
	People_Player::connect_with_net_server();
	send(People_Player::server_connectfd, "0", 1, 0);//发送一个寻找对手的密文
	CCLOG("People_Player::server_connectfd = %d ", People_Player::server_connectfd);
	std::thread thread1(People_Player::run_recv_with_serverthread);//创建一个线程来接收获取服务器端的数据
	thread1.detach();

}
void Start_Game_Layer::quit_menu_callfunc(Ref * ref)
{
	Director::getInstance()->end();
}