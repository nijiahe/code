#include"MyScene.h"
#include"MyLayer.h"
/*
MyScene* MyScene::create()
{
	MyScene* pRet = new MyScene();
	if ( pRet && pRet->init())
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

//这里实现了将layer add进 scene,其他均无用,整合进了Mylayer::createscene中
bool MyScene::init()
{
	Scene::init();
	MyLayer* layer = MyLayer::create();
	this->addChild(layer);
	return true;
}