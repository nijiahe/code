#include "Grounds_Select_Layer.h"
#include "Game_Layer.h"
#include "Start_Layer.h"

bool Grounds_Select_Layer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//����ͼƬ
	Sprite * spr = Sprite::create("BackGround/bg.png");
	addChild(spr);
	spr->setPosition(Winsize.width*0.5, Winsize.height*0.5);
	spr->setContentSize(Size(Winsize.width, Winsize.height));

	Node * node = Node::create();
	for (int i = 1; i <= _Rounds_count; i++)
	{
		Sprite * spr = Sprite::create(Common::format("Rounds/select", i,".jpg"));
		node->addChild(spr);
		spr->setTag(i + 100);
		spr->setPosition(Winsize.width*0.5+Winsize.width*(i-1), Winsize.height*0.5);
		spr->setAnchorPoint(Vec2(0.5, 0.5));
	}
	_view = ScrollView::create(Winsize, node);
	addChild(_view);
	_view->setDirection(ScrollView::Direction::HORIZONTAL);
	_view->setContentSize(Size(Winsize.width*8,Winsize.height));
	_view->setSwallowTouches(false);
	//view->setBounceable(false);

	//���ذ�ť
	MenuItem * back_item = MenuItemImage::create("UI/backA.png", "UI/backB.png", CC_CALLBACK_1(Grounds_Select_Layer::back_menu_callback, this));
	back_item->setPosition(Winsize.width*0.5-back_item->getContentSize().width,-Winsize.height*0.5+back_item->getContentSize().height+20);
	back_item->setScale(1.5);
	Menu * menu = Menu::create(back_item, NULL);
	addChild(menu);

	//��������
	runtouch();


	return true;
}


void Grounds_Select_Layer::runtouch()
{
	EventListenerTouchOneByOne * mylistener = EventListenerTouchOneByOne::create();//����һ����������
	mylistener->setSwallowTouches(false);
	mylistener->onTouchBegan = [=](Touch* touch, Event* event) mutable//ָ����ʱ
	{ 
		return true;
	};

	mylistener->onTouchMoved = [=](Touch* touch, Event* event) mutable//ָ�ƶ�ʱ
	{
		
	};
	mylistener->onTouchEnded = [=](Touch* touch, Event* event) //�ɿ�ʱ
	{
		if (isclick(touch))
		{
			Node * node = _view->getContainer();
			Vec2 ptnode = node->convertTouchToNodeSpace(touch);
			for (int i = 1; i <= _Rounds_count; i++)
			{
				Sprite * spr = (Sprite *)node->getChildByTag(100 + i);
				if (spr->getBoundingBox().containsPoint(ptnode))
				{
					Director::getInstance()->replaceScene(Common::createscene(Game_Layer::create(i,NULL)));
				}
			}
		}
	};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(mylistener, this);
}

bool Grounds_Select_Layer::isclick(Touch* touch)
{
	Vec2 start_location = touch->getStartLocation();
	Vec2 location = touch->getLocation();
	return start_location.getDistanceSq(location)<25;
}

void Grounds_Select_Layer::back_menu_callback(Ref * ref)
{
	Start_Layer * layer = Start_Layer::create();
	Scene * scene = Common::createscene(layer);
	Director::getInstance()->replaceScene(scene);
}