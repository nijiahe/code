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

//����ʵ���˽�layer add�� scene,����������,���Ͻ���Mylayer::createscene��
bool MyScene::init()
{
	Scene::init();
	MyLayer* layer = MyLayer::create();
	this->addChild(layer);
	return true;
}