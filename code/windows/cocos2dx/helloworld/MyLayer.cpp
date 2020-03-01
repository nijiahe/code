#include"MyLayer.h"

/*
MyLayer* MyLayer::create()
{
	MyLayer* pRet = new MyLayer();
	if (pRet&&pRet->init())
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
*/

bool MyLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//get visible size
	Size visibleSize = Director::getInstance()->getWinSize();

	//create a sprite of picture
	Sprite* spr = Sprite::create("ailuomang.jpg");

	/*
	CC_DEPRECATED_ATTRIBUTE inline Vec2 ccp(float x, float y)
	{
		return Vec2(x, y);
	}
	*/
	//ccp and Vec2 is same
	spr->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	addChild(spr);

	return true;
}

Scene* MyLayer::createscene()
{
	Scene* scene = Scene::create();//这里不用调用自己写的Myscene类,这里将其add进layer的功能整合
	MyLayer* layer = MyLayer::create();
	scene->addChild(layer);
	return scene;
}