#include "COBatchNode.h"

bool COBatchNode::init()
{
	if (!Layer::init())
	{
		return false;
	}
	/*EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
	EventListenerTouchOneByOne* myListener = EventListenerTouchOneByOne::create();

	//���費���Ӵ˾���Ϣ��Ȼ�����´���  
	myListener->setSwallowTouches(true);*/
	Size visible = Director::getInstance()->getWinSize();
	
	return true;
}

Scene* COBatchNode::createscene()
{
	Scene* scene = Scene::create();
	COBatchNode* layer = COBatchNode::create();
	scene->addChild(layer);

	/*���������ŵı�����һ��֡����*/
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("zombie.plist");//���仺�浽�ڴ�

	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ailuomang.jpg");//�ȰѴ�ͼ�ӵ��ڴ���ȥ

	/*��������ǽ�һ��ͼƬ��ŵ��ڴ�*/
	Texture2D* texture = Director::getInstance()->getTextureCache()->addImage("ailuomang.jpg");
	SpriteBatchNode* node = SpriteBatchNode::create("ailuomang.jpg");//�ٰѴ�ͼ��Ⱦ

	layer->addChild(node);
	Size visible = Director::getInstance()->getWinSize();

	EventListenerTouchOneByOne* listener1 = EventListenerTouchOneByOne::create();//����һ����������    
	listener1->setSwallowTouches(true);//�����Ƿ����´��ݴ���
	Rect rect = Rect(0, 0, visible.width, visible.height);//���ô�������
	listener1->onTouchBegan = [=](Touch* touch, Event* event)//ָ����ʱ
	{ //[]�м���Ǵ���Ĳ���  
		auto target = static_cast<Sprite*>(event->getCurrentTarget());//��ȡ�ĵ�ǰ������Ŀ��  
		CCLOG("TouchBegan");
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());//��ȡ��������
		Size s = target->getContentSize();
		if (rect.containsPoint(locationInNode))//�жϴ������Ƿ���Ŀ��ķ�Χ��
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

	listener1->onTouchMoved = [=](Touch* touch, Event* event)//ָ�ƶ�ʱ
	{
		CCLOG("TouchMoved");
	};

	listener1->onTouchEnded = [=](Touch* touch, Event* event) //�ɿ�ʱ
	{ 
		CCLOG("TouchEnded");
	};

	layer->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, node);

	return scene;

}


