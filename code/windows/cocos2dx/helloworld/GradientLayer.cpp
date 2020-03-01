#include "GradientLayer.h"

bool GradientLayer::init()
{
	if (!GradientLayer::initWithColor(Color4B(255,0,0,255),Color4B(0,0,255,255),Vec2(-1,0)))
	{
		return false;
	}
	//get visible size
	Size visibleSize = Director::getInstance()->getWinSize();

	return true;
}

Scene* GradientLayer::createscene()
{
	Scene* scene = Scene::create();//这里不用调用自己写的Myscene类,这里将其add进layer的功能整合
	GradientLayer* layer = GradientLayer::create();
	scene->addChild(layer);
	return scene;
}