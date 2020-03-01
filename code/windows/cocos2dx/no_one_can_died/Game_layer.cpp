#include "Game_layer.h"
#include "Game_back_layer.h"
#include "GameEnd.h"

bool Game_layer::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}
	Size visible = Director::getInstance()->getWinSize();
	this->setContentSize(Size(visible.width, visible.height / 3 - 10));
	add_floor();
	add_people();
	runschedule();
	runtouch(); 
	run_hero_standon_schedule(0);
	return true;
}


Scene * Game_layer::createscene()
{
	Scene * scene = Scene::create();
	Game_layer * layer = Game_layer::create();
	scene->addChild(layer);
	return scene;
}

void Game_layer::add_floor()
{
	Size visible = Director::getInstance()->getWinSize();
	Sprite * floor = Sprite::create();
	floor->setTag(floortag);
	floor->setTextureRect(Rect(0, 0, visible.width, 4));
	floor->setColor(Color3B(0, 0, 0));
	floor->setAnchorPoint(Vec2(0, 0));
	floor->setPosition(Vec2(0, 0));
	addChild(floor);
}

void Game_layer::add_people()
{
	Size visible = Director::getInstance()->getWinSize();
	Sprite * hero = Sprite::create("hero/hero.png");
	hero->setTag(herotag);
	hero->setPosition(50, 4);
	hero->setAnchorPoint(Vec2(0, 0));
	addChild(hero);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("hero/run.plist");
	Vector<SpriteFrame*> vec;
	for (int i = 1; i <= 15; i++)
	{
		__String* str = __String::createWithFormat("run%d.png", i);
		SpriteFrame * frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str->getCString());
		vec.pushBack(frame);
	}
	Animation * animation = Animation::createWithSpriteFrames(vec);
	animation->setDelayPerUnit(0.1f);//设置没一个动作放几秒
	animation->setLoops(-1);

	Animate * animate = Animate::create(animation);
	hero->runAction(animate);
}

void Game_layer::add_bar()
{
	Size visible = Director::getInstance()->getWinSize();
	bar * _bar = bar::create();
	addChild(_bar);
	bar_vector.pushBack(_bar);
	_bar->setPosition(visible.width+_bar->getContentSize().width, 0);
}

void Game_layer::runschedule()
{
	schedule(SEL_SCHEDULE(&Game_layer::schedule_callback));
}
void Game_layer::schedule_callback(float t)
{
	bar_Completion++;
	if (bar_Completion >= bar_threshold)
	{
		reset_bar();
		add_bar();
	}
	for (int i = bar_vector.size() -1; i >=0; i--)
	{
		bar * bar = bar_vector.at(i);
		if (bar->getPositionX() + bar->getContentSize().width < 0)
		{
			bar->removeFromParent();
			bar_vector.erase(i);
		}
		else
		{
			Sprite * hero = dynamic_cast<Sprite *>(getChildByTag(herotag));
			Rect rect = hero->getBoundingBox();
			rect.size.width -= 30;
			rect.origin.x += 15;
			if (rect.intersectsRect(bar->getBoundingBox()))
			{
				Scene * scene = GameEnd::createscene(dynamic_cast<Game_back_layer *>(this->getParent())->degree_of_difficulty);
				Director::getInstance()->replaceScene(scene);
			}
		}
	}
}

void Game_layer::reset_bar()
{
	bar_Completion = 0;
	bar_threshold = rand() % 80 +80;
}

void Game_layer::runtouch()
{
	Size visible = Director::getInstance()->getWinSize();

	EventListenerTouchOneByOne* mylistener = EventListenerTouchOneByOne::create();
	Rect rect = this->getBoundingBox();
	mylistener->setSwallowTouches(false);
	mylistener->onTouchBegan = [=](Touch* touch, Event* event) mutable//指按下时
	{ 
		Vec2 pt = touch->getLocation();
		if (this->getBoundingBox().containsPoint(pt))
		{
			Sprite * hero = dynamic_cast<Sprite *>(getChildByTag(herotag));
			if (this->stand_on_thing)
			{
				MoveBy * moveby = MoveBy::create(0.5, Vec2(0, visible.height*0.25));
				hero->runAction(moveby);
				unschedule(CC_SCHEDULE_SELECTOR(Game_layer::hero_land_schedule_callback));
				scheduleOnce(SEL_SCHEDULE(&Game_layer::run_hero_standon_schedule), 0.5);
				this->stand_on_thing = false;
			}
			
			return true;
		}
		return false;
	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(mylistener, this);
}

void Game_layer::hero_land_schedule_callback(float t)
{
	Sprite * hero = dynamic_cast<Sprite *>(getChildByTag(herotag));
	Size visible = Director::getInstance()->getWinSize();
	if (!is_hero_standon_something())
	{
		hero->setPositionY(hero->getPositionY() - visible.height*0.5 / 60);
	}
}

bool Game_layer::is_hero_standon_something()
{
	Sprite * hero = dynamic_cast<Sprite *>(getChildByTag(herotag));
	Sprite * floor = dynamic_cast<Sprite *>(getChildByTag(floortag));
	if (hero->getPositionY() - floor->getPositionY() -floor->getContentSize().height <= 6 &&
		hero->getPositionY() - floor->getPositionY() - floor->getContentSize().height >= -4)
	{
		hero->setPositionY(floor->getPositionY() + floor->getContentSize().height + 1);
		stand_on_thing = true;
		return true;
	}
	else if (is_hero_standon_bar())
	{
		stand_on_thing = true;
		return true;
	}
	else
	{
		stand_on_thing = false;
		return false;
	}
}

bool Game_layer::is_hero_standon_bar()
{
	Sprite * hero = dynamic_cast<Sprite *>(getChildByTag(herotag));
	for (int i = bar_vector.size() - 1; i >= 0; i--)
	{
		if (hero->getPositionY() - bar_vector.at(i)->getPositionY()- bar_vector.at(i)->getContentSize().height <= 8 &&
			hero->getPositionY() - bar_vector.at(i)->getPositionY() - bar_vector.at(i)->getContentSize().height >= 0&&
			hero->getPositionX()+hero->getContentSize().width>= bar_vector.at(i)->getPositionX()&& 
			hero->getPositionX()<= bar_vector.at(i)->getPositionX()+ bar_vector.at(i)->getContentSize().width)
		{
			hero->setPositionY(bar_vector.at(i)->getPositionY() + bar_vector.at(i)->getContentSize().height + 1);
			stand_on_thing = bar_vector.at(i);
			return true;
		}
	}
	return false;
}

void Game_layer::run_hero_standon_schedule(float t)
{
	schedule(SEL_SCHEDULE(&Game_layer::hero_land_schedule_callback));
}