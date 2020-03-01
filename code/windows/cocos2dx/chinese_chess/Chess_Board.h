#ifndef __Chess_Board_H__
#define __Chess_Board_H__

#include "cocos2d.h"
USING_NS_CC;

#include "Chess_Color.h"

class Chesspiece_Place;
class Chesspiece;
class PLayer;
class Chess_Step;

class Chess_Board:public LayerColor
{
public:
	CREATE_FUNC(Chess_Board);
	bool init();
	void add_chess_board_background();//������̱���ͼƬ
	static Scene * createscene();
	Chesspiece_Place Converto_Chess_Place(Vec2 position);//ת��������λ������
	Vec2 Converto_Layer_Position(Chesspiece_Place position);//ת����ͼ��λ������
	void runtouch();//��������
	void closetouch();//�رմ���
	void monitor_touch();//������ʱ��
	void monitor_touch_callback(float t);//��ʱ���ص�����
	Chess_Step * get_current_step_and_clean(PLayer * player);//�õ���ǰ��ҵĲ���
	void run_step(Chess_Step * step);//ִ�в���
	void monitor_notice();//֪ͨ��ʱ��֪ͨ����ļ�����
	void notice_other_player(float t);//֪ͨ�Է�Ӧ��������
	void regret(int num);
	void return_step(Chess_Step * step);

	
	bool is_has_chesspiece(Chesspiece_Place position);//�Ƿ�������
	bool is_has_red_chesspiece(Chesspiece_Place position);//�Ƿ��к���
	bool is_has_black_chesspiece(Chesspiece_Place position);//�Ƿ��к���
	bool is_has_samecolor_chesspiece(Chesspiece * chess, Chesspiece_Place position);//�Ƿ�����ͬ��ɫ������
	bool is_has_differentcolor_chesspiece(Chesspiece * chess, Chesspiece_Place position);//�Ƿ��в�ͬ��ɫ������
	bool is_has_chesspiece_among(Chesspiece_Place origin_position, Chesspiece_Place des_position);//�м��Ƿ�������
	bool is_has_onlyone_chesspiece_among(Chesspiece_Place origin_position, Chesspiece_Place des_position);//�м��Ƿ�ֻ��һ������
	bool is_has_cross_river(Chesspiece * chess, Chesspiece_Place position);//�Ƿ����
	bool is_has_outof_home(Chesspiece * chess,Chesspiece_Place position);//�Ƿ����Ӫ

	Chesspiece_Place get_different_jiang_position(Chesspiece * chess);//�õ��Է�������λ��
	bool is_has_chesspiece(Chesspiece * chess,Chesspiece_Place position_by);//�Ƿ�������
	bool is_has_red_chesspiece(Chesspiece * chess,Chesspiece_Place position_by);//�Ƿ��к���
	bool is_has_black_chesspiece(Chesspiece * chess, Chesspiece_Place position_by);//�Ƿ��к���
	bool is_has_samecolor_chesspiece_by(Chesspiece * chess, Chesspiece_Place position_by);//�Ƿ�����ͬ��ɫ������
	bool is_has_differentcolor_chesspiece_by(Chesspiece * chess, Chesspiece_Place position_by);//�Ƿ�����ͬ��ɫ������
	bool is_has_chesspiece_among(Chesspiece * origin_chess, Chesspiece * des_chess);//�м��Ƿ�������
	bool is_has_onlyone_chesspiece_among(Chesspiece * origin_chess, Chesspiece * des_chess);//�м��Ƿ�ֻ��һ������
	bool is_has_cross_river_by(Chesspiece * chess, Chesspiece_Place position_by);//�Ƿ����
	bool is_has_outof_home_by(Chesspiece * chess, Chesspiece_Place position_by);//�Ƿ����Ӫ
	Chesspiece_Place get_different_jiang_position_by(Chesspiece * chess);//�õ��Է������λ��
	
	bool is_has_in_cross(Chesspiece * chess);//�Ƿ����Ӷ���

	void switch_current_color();//�л���ǰ�������ɫ;
	Chesspiece * find_chesspiece_by_position(Chesspiece_Place position);//����λ��Ѱ������
	void add_select_picture(Chesspiece * select_chesspiece);//���ѡ��ͼƬ
	void add_red_select_picture(Chesspiece * select_chesspiece);//��Ӻ�ɫ��ѡ��ͼƬ

	enum tag
	{
		background_tag,
	};

	enum player_type
	{
		AI,
		People,
	};

	void draw_chessboard_test();//���߲��Ժ���

	bool is_notice = false;
	Sprite * _background;
	Chess_Color _current_color;
	Chesspiece * _select_chesspiece;
	Sprite * _select_picture;
	Sprite * _red_select_picture;
	EventListenerTouchOneByOne* mylistener=nullptr;//���ڿ��ƴ���
	Vector<Chesspiece *> _chess_vec;
	PLayer * _me;
	PLayer * _other_player;
	player_type _player_type;
	
};

#endif

