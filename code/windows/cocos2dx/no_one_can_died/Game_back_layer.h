#ifndef __Game_back_layer_H_
#define __Game_back_layer_H_

#include "cocos2d.h"
USING_NS_CC;

class Game_back_layer :public LayerColor
{
public:
	static Game_back_layer * create(int degree_of_difficulty);
	static Scene * createscene(int degree_of_difficulty);
	bool init(int degree_of_difficulty);

	int degree_of_difficulty;
};
#endif

