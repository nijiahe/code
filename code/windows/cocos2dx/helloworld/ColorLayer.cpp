#include "ColorLayer.h"

bool ColorLayer::init()
{
	/*
	ccc4(const GLubyte r, const GLubyte g, const GLubyte b, const GLubyte o)
	{
		return Color4B(r, g, b, o);
	}
	*/
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}
	//get visible size
	Size visibleSize = Director::getInstance()->getWinSize();

	return true;
}

Scene* ColorLayer::createscene()
{
	Scene* scene = Scene::create();//这里不用调用自己写的Myscene类,这里将其add进layer的功能整合
	ColorLayer* layer = ColorLayer::create();
	scene->addChild(layer);
	return scene;
}