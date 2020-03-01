#include "Game_back_layer.h"
#include "Game_layer.h"

bool Game_back_layer::init(int degree_of_difficulty)
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}
	this->degree_of_difficulty = degree_of_difficulty;
	Size visible = Director::getInstance()->getWinSize();
	
	for (int i = 0; i < degree_of_difficulty; i++)
	{
		Game_layer * layer = Game_layer::create();
		layer->setPosition(0, visible.height / 3 * (i+0.1));
		layer->setAnchorPoint(Vec2(0, 0));
		addChild(layer);
	}

	return true;
}


Scene * Game_back_layer::createscene(int degree_of_difficulty)
{
	Scene * scene = Scene::create();
	Game_back_layer * layer = Game_back_layer::create(degree_of_difficulty);
	scene->addChild(layer);
	return scene;
}

Game_back_layer * Game_back_layer::create(int degree_of_difficulty)
{
	Game_back_layer * pRet = new Game_back_layer;
	if (pRet&&pRet->init(degree_of_difficulty))
	{
		pRet->autorelease();
	}
	else
	{
		delete pRet;
		pRet = NULL;
	}
	return pRet;
}