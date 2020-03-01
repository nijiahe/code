#include "Coordinate.h"

bool Coordinate::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//get visible size
	/*setTouchEnabled(true);//打开触摸开关
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);//单点    
		已被否决*/
	auto myListener = EventListenerTouchOneByOne::create();
	myListener->setSwallowTouches(true);

	Sprite* big = Sprite::create();
	big->setTextureRect(Rect(0, 0, 150, 150));
	big->setColor(Color3B::RED);
	big->setPosition(100, 100);
	big->setAnchorPoint(Vec2(0, 0));
	this->addChild(big);

	Sprite* little = Sprite::create();
	little->setTextureRect(Rect(0, 0, 50, 50));
	little->setColor(Color3B::YELLOW);
	little->setPosition(150, 150);
	little->setAnchorPoint(Vec2(1, 1));
	big->addChild(little);
	
	/*这里得到的实质是父精灵的Position到子精灵Position的距离*/
	CCLOG("little.x=%f,little.y=%f", little->getPositionX(), little->getPositionY());

	/*获得世界坐标*/
	/*这个函数的实质:调用对象作为参考系,计算调用对象的Position到子对象Position的距离,及求两个POSITION之和,适用于子父精灵之间*/
	//Vec2 toworld = big->convertToWorldSpace(little->getPosition());

	/*这个函数的实质:求两个POSITION之差,适用于在同一父精灵之上的子精灵之间*/
	Vec2 toworld = big->convertToNodeSpace(little->getPosition());
	CCLOG("toworld.x=%f,toworld.y=%f", toworld.x, toworld.y);

	/*内部代码渲染是递归实现的,先渲染父精灵,再渲染子精灵*/
	MoveBy* by = MoveBy::create(2, Vec2(200, 0));//创建第一个动作
	MoveBy* by2 = by->reverse();//创建第二个动作
	Sequence* seq = Sequence::create(by, by2, NULL);//创建动作集,是可变参函数,可变惨函数最后一个参数为0
	big->runAction(RepeatForever::create(seq));

	MoveBy* lby = MoveBy::create(2, Vec2(0, -100));//创建第一个动作
	MoveBy* lby2 = lby->reverse();//创建第二个动作
	Sequence* lseq = Sequence::create(lby, lby2, NULL);//创建动作集,是可变参函数,可变惨函数最后一个参数为0
	little->runAction(RepeatForever::create(lseq));

	return true;
}

Scene* Coordinate::createscene()
{
	Scene* scene = Scene::create();
	Coordinate* layer = Coordinate::create();
	//layer->setPosition(Vec2(-400, 0));
	scene->addChild(layer);
	return scene;
}

