#include "plant_vs_zombie_Layer.h"

Scene* plant_vs_zombie_Layer::createscene()
{
	Scene* scene = new Scene;
	plant_vs_zombie_Layer* p_vs_z = plant_vs_zombie_Layer::create();
	scene->addChild(p_vs_z);
	return scene;
}
plant_vs_zombie_Layer* plant_vs_zombie_Layer::create()
{
	plant_vs_zombie_Layer* pRet = new plant_vs_zombie_Layer();
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

bool plant_vs_zombie_Layer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visible = Director::getInstance()->getWinSize();
	//RectҲ��һ����
	//������������
	Sprite* background = Sprite::create("background.jpg",Rect(0,0,visible.width,visible.height));
	background->setAnchorPoint(Vec2(0, 0));
	background->setPosition(Vec2(0, 0));
	addChild(background);

	//����plant����
	//OPEN GL�ӿ�û���ṩcreate����,��Ҫnew
	Image* image = new Image();
	image->autorelease();
	image->initWithImageFile("plant.png");

	Texture2D* tecture = new Texture2D();
	tecture->autorelease();
	tecture->initWithImage(image);

	Sprite* plant = Sprite::createWithTexture(tecture);//����  �ڴ��Ż�
	plant->setAnchorPoint(Vec2(0, 0));
	plant->setPosition(Vec2(visible.width/2-140, visible.height/2-90));
	addChild(plant);

	//////////////////////////////

	//������ͼƬ�ӵ��ڴ��� (��һ�źܴ��ͼƬ��װ)
	//Texture2D* texture=TextureCache::getInstance()->addImage("bullet.png"); ������Ϊ�ѷ��
	Texture2D* texture = Director::getInstance()->getTextureCache()->addImage("bullet.png");
	Sprite* bullet = Sprite::createWithTexture(texture);
	bullet->setAnchorPoint(Vec2(0, 0));
	bullet->setPosition(Vec2(visible.width/2, visible.height/2-50));
	addChild(bullet);

	///////////// 
	//����  ����˺ܶ�֡
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("zombie.plist");//���仺�浽�ڴ�

	SpriteFrame* sf1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("z_1_attack_01.png");
	Sprite* zombie1 = Sprite::createWithSpriteFrame(sf1);
	// �� Sprite* zombie2 = Sprite::createWithSpriteFrameName("z_1_attack_01.png"); 
	zombie1->setAnchorPoint(Vec2(0, 0));
	zombie1->setPosition(Vec2(visible.width / 2 + 20, visible.height / 2 - 90));
	addChild(zombie1);

	//ÿ������һ��,    �� ���ĸ߶�,���Ĵ���
	JumpBy* jumpby = JumpBy::create(2, Vec2(0, 0), 40, 3);
	zombie1->runAction(jumpby);
	zombie1->runAction(RepeatForever::create(jumpby));
	
	SpriteFrame* sf2 = SpriteFrame::create("p_1_01.png", Rect(0, 0, 80, 80));
	Sprite* sunflower = Sprite::createWithSpriteFrame(sf2);
	sunflower->setAnchorPoint(Vec2(0, 0));
	sunflower->setPosition(Vec2(visible.width / 2-10, visible.height / 2 - 90));

	addChild(sunflower);

	/*ZOrderԽ��Խ��ǰ��*/
	background->setLocalZOrder(0);
	bullet->setLocalZOrder(1000);
	zombie1->setLocalZOrder(1001);
	sunflower->setLocalZOrder(100);
	return true;
}