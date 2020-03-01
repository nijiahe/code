#include "memory.h"

bool memory::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}
	/*Sprite* spr = Sprite::create("ailuomang.jpg");//create���Ѿ������autorelease
	CCLOG("retain count %d", spr->getReferenceCount());
	spr->setTag(picture1);
	addChild(spr);
	//spr->autorelease();//��һ֡�Ժ��1
	Size visible = Director::getInstance()->getWinSize();
	spr->setPosition(visible.width / 2, visible.height / 2);
	CCLOG("retain count %d", spr->getReferenceCount());
	/*schedule(CC_SCHEDULE_SELECTOR(memory::myschedule), 3);//ÿ����ִ��һ��*/
	
	/*typedef void (Ref::*SEL_MenuHandler)(Ref*);*/
	/*MenuItemImage * MenuItemImage::create(const std::string& normalImage, const std::string& selectedImage, const ccMenuCallback& callback)
	{
		return MenuItemImage::create(normalImage, selectedImage, "", callback);
	}
	*/
	array = __Array::create();
	Sprite* spr = Sprite::create("bullet.png");
	/*�������retain(),������������޷����ӵ���Ⱦ����ȥ,ֻ�����1֡,1֡�Ժ�_Array�Զ���release(),��Ϊ��ReferenceCountΪ0,�˴�Ӧ����ȡ��_Array����+1�İ취*/
	array->addObject(spr);//���������ӵ�������ȥ
	array->retain();
	MenuItemImage* Item = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(memory::menucallback, this));
	Menu* menu = Menu::create(Item, NULL);
	MenuItemFont;
	MenuItemLabel;
	MenuItemAtlasFont;
	MenuItemSprite;
	Menu;
	addChild(menu);
	return true;
}

Scene* memory::createscene()
{
	Scene* scene = Scene::create();
	memory* layer = memory::create();
	scene->addChild(layer);

	return scene;
}

/*
void memory::myschedule(float dt)
{
	Sprite* spr=dynamic_cast<Sprite*>(getChildByTag(picture1));
	//CCLOG("retain count %d", spr->getReferenceCount());
	if (spr)
	{
		spr->removeFromParent();
		spr = NULL;
	}
}
*/

void memory::menucallback(Ref* ref)
{
	CCLOG("111");
	/*ȡ�������еľ���*/
	/*��ȡ�����һ��������ͬ1��,�����ظ���ӵ���Ⱦ����*/
	Sprite* spr=dynamic_cast<Sprite*>(array->getLastObject());
	if (spr)
	{
		Size visible = Director::getInstance()->getWinSize();
		srand(time(0));
		/*��������std::randʵ�ֵ�*/
		spr->setPosition(CCRANDOM_0_1()*visible.width , CCRANDOM_0_1()*visible.height );
		//spr->setPosition(240,160);
		addChild(spr);
	}
}

void memory::onExit()
{
	array->release();
	CCLOG("onExit");
}

/*
void memory::onEnter()
{
	CCLOG("onEnter");
}
*/