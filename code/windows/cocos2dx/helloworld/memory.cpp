#include "memory.h"

bool memory::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}
	/*Sprite* spr = Sprite::create("ailuomang.jpg");//create里已经完成了autorelease
	CCLOG("retain count %d", spr->getReferenceCount());
	spr->setTag(picture1);
	addChild(spr);
	//spr->autorelease();//过一帧以后减1
	Size visible = Director::getInstance()->getWinSize();
	spr->setPosition(visible.width / 2, visible.height / 2);
	CCLOG("retain count %d", spr->getReferenceCount());
	/*schedule(CC_SCHEDULE_SELECTOR(memory::myschedule), 3);//每三秒执行一次*/
	
	/*typedef void (Ref::*SEL_MenuHandler)(Ref*);*/
	/*MenuItemImage * MenuItemImage::create(const std::string& normalImage, const std::string& selectedImage, const ccMenuCallback& callback)
	{
		return MenuItemImage::create(normalImage, selectedImage, "", callback);
	}
	*/
	array = __Array::create();
	Sprite* spr = Sprite::create("bullet.png");
	/*如果不用retain(),由于这个数组无法被加到渲染树上去,只会存在1帧,1帧以后_Array自动被release(),因为其ReferenceCount为0,此处应当采取将_Array数组+1的办法*/
	array->addObject(spr);//将这个精灵加到数组中去
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
	/*取出数组中的精灵*/
	/*获取的最后一个精灵是同1个,不能重复添加到渲染树上*/
	Sprite* spr=dynamic_cast<Sprite*>(array->getLastObject());
	if (spr)
	{
		Size visible = Director::getInstance()->getWinSize();
		srand(time(0));
		/*本质是用std::rand实现的*/
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