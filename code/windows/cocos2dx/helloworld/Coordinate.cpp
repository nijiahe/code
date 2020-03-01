#include "Coordinate.h"

bool Coordinate::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//get visible size
	/*setTouchEnabled(true);//�򿪴�������
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);//����    
		�ѱ����*/
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
	
	/*����õ���ʵ���Ǹ������Position���Ӿ���Position�ľ���*/
	CCLOG("little.x=%f,little.y=%f", little->getPositionX(), little->getPositionY());

	/*�����������*/
	/*���������ʵ��:���ö�����Ϊ�ο�ϵ,������ö����Position���Ӷ���Position�ľ���,��������POSITION֮��,�������Ӹ�����֮��*/
	//Vec2 toworld = big->convertToWorldSpace(little->getPosition());

	/*���������ʵ��:������POSITION֮��,��������ͬһ������֮�ϵ��Ӿ���֮��*/
	Vec2 toworld = big->convertToNodeSpace(little->getPosition());
	CCLOG("toworld.x=%f,toworld.y=%f", toworld.x, toworld.y);

	/*�ڲ�������Ⱦ�ǵݹ�ʵ�ֵ�,����Ⱦ������,����Ⱦ�Ӿ���*/
	MoveBy* by = MoveBy::create(2, Vec2(200, 0));//������һ������
	MoveBy* by2 = by->reverse();//�����ڶ�������
	Sequence* seq = Sequence::create(by, by2, NULL);//����������,�ǿɱ�κ���,�ɱ�Һ������һ������Ϊ0
	big->runAction(RepeatForever::create(seq));

	MoveBy* lby = MoveBy::create(2, Vec2(0, -100));//������һ������
	MoveBy* lby2 = lby->reverse();//�����ڶ�������
	Sequence* lseq = Sequence::create(lby, lby2, NULL);//����������,�ǿɱ�κ���,�ɱ�Һ������һ������Ϊ0
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

