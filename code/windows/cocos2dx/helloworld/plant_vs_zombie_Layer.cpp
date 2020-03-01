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
	//Rect也是一个类
	//创建背景精灵
	Sprite* background = Sprite::create("background.jpg",Rect(0,0,visible.width,visible.height));
	background->setAnchorPoint(Vec2(0, 0));
	background->setPosition(Vec2(0, 0));
	addChild(background);

	//创建plant精灵
	//OPEN GL接口没有提供create函数,需要new
	Image* image = new Image();
	image->autorelease();
	image->initWithImageFile("plant.png");

	Texture2D* tecture = new Texture2D();
	tecture->autorelease();
	tecture->initWithImage(image);

	Sprite* plant = Sprite::createWithTexture(tecture);//纹理  内存优化
	plant->setAnchorPoint(Vec2(0, 0));
	plant->setPosition(Vec2(visible.width/2-140, visible.height/2-90));
	addChild(plant);

	//////////////////////////////

	//将这张图片加到内存里 (用一张很大的图片包装)
	//Texture2D* texture=TextureCache::getInstance()->addImage("bullet.png"); 被声明为已否决
	Texture2D* texture = Director::getInstance()->getTextureCache()->addImage("bullet.png");
	Sprite* bullet = Sprite::createWithTexture(texture);
	bullet->setAnchorPoint(Vec2(0, 0));
	bullet->setPosition(Vec2(visible.width/2, visible.height/2-50));
	addChild(bullet);

	///////////// 
	//缓存  存放了很多帧
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("zombie.plist");//将其缓存到内存

	SpriteFrame* sf1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("z_1_attack_01.png");
	Sprite* zombie1 = Sprite::createWithSpriteFrame(sf1);
	// 或 Sprite* zombie2 = Sprite::createWithSpriteFrameName("z_1_attack_01.png"); 
	zombie1->setAnchorPoint(Vec2(0, 0));
	zombie1->setPosition(Vec2(visible.width / 2 + 20, visible.height / 2 - 90));
	addChild(zombie1);

	//每两秒跳一次,    ， 跳的高度,跳的次数
	JumpBy* jumpby = JumpBy::create(2, Vec2(0, 0), 40, 3);
	zombie1->runAction(jumpby);
	zombie1->runAction(RepeatForever::create(jumpby));
	
	SpriteFrame* sf2 = SpriteFrame::create("p_1_01.png", Rect(0, 0, 80, 80));
	Sprite* sunflower = Sprite::createWithSpriteFrame(sf2);
	sunflower->setAnchorPoint(Vec2(0, 0));
	sunflower->setPosition(Vec2(visible.width / 2-10, visible.height / 2 - 90));

	addChild(sunflower);

	/*ZOrder越大越在前面*/
	background->setLocalZOrder(0);
	bullet->setLocalZOrder(1000);
	zombie1->setLocalZOrder(1001);
	sunflower->setLocalZOrder(100);
	return true;
}