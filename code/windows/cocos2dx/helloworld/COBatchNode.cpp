#include "COBatchNode.h"

bool COBatchNode::init()
{
	if (!Layer::init())
	{
		return false;
	}
	/*EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
	EventListenerTouchOneByOne* myListener = EventListenerTouchOneByOne::create();

	//假设不增加此句消息依然会向下传递  
	myListener->setSwallowTouches(true);*/
	Size visible = Director::getInstance()->getWinSize();
	
	return true;
}

Scene* COBatchNode::createscene()
{
	Scene* scene = Scene::create();
	COBatchNode* layer = COBatchNode::create();
	scene->addChild(layer);

	/*这个函数存放的必须是一个帧集合*/
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("zombie.plist");//将其缓存到内存

	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ailuomang.jpg");//先把大图加到内存里去

	/*这个函数是将一张图片存放到内存*/
	Texture2D* texture = Director::getInstance()->getTextureCache()->addImage("ailuomang.jpg");
	SpriteBatchNode* node = SpriteBatchNode::create("ailuomang.jpg");//再把大图渲染

	layer->addChild(node);
	Size visible = Director::getInstance()->getWinSize();

	EventListenerTouchOneByOne* listener1 = EventListenerTouchOneByOne::create();//创建一个触摸监听    
	listener1->setSwallowTouches(true);//设置是否想下传递触摸
	Rect rect = Rect(0, 0, visible.width, visible.height);//设置触摸区域
	listener1->onTouchBegan = [=](Touch* touch, Event* event)//指按下时
	{ //[]中间的是传入的参数  
		auto target = static_cast<Sprite*>(event->getCurrentTarget());//获取的当前触摸的目标  
		CCLOG("TouchBegan");
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());//获取精灵区域
		Size s = target->getContentSize();
		if (rect.containsPoint(locationInNode))//判断触摸点是否在目标的范围内
		{
			for (int i = 0; i < 1000; i++)
			{
				Sprite* spr = Sprite::createWithTexture(texture);
				//Sprite* spr = Sprite::createWithSpriteFrameName("ailuomang.jpg");
				spr->setPosition(Vec2(CCRANDOM_0_1()*visible.width, CCRANDOM_0_1()*visible.height));
				node->addChild(spr);
			}
			
		}
		return true;
	};

	listener1->onTouchMoved = [=](Touch* touch, Event* event)//指移动时
	{
		CCLOG("TouchMoved");
	};

	listener1->onTouchEnded = [=](Touch* touch, Event* event) //松开时
	{ 
		CCLOG("TouchEnded");
	};

	layer->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, node);

	return scene;

}


