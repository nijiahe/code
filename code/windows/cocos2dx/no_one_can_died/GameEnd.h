#ifndef __GameEnd_H_
#define __GameEnd_H_

#include "cocos2d.h"
USING_NS_CC;

class GameEnd :public LayerColor
{
public:
	static GameEnd * create(int degree_of_difficulty);
	static Scene * createscene(int degree_of_difficulty);
	bool init(int degree_of_difficulty);
	void again_menu_callback(Ref * ref);
	void back_menu_callback(Ref * ref);


	int degree_of_difficulty;
};
#endif

