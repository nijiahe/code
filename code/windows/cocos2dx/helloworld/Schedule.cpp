#include "Schedule.h"

bool Schedule::init()
{
	if (!Layer::init())
	{
		return false;
	}

	/************************/
	//定时器调用的实质都是_scheduler->schedule
	/************************/

	//scheduleUpdate();//启动帧循环定时器 会自动按照每帧执行一次override的update函数

	/*typedef和define详见CCRef.h*/
	//scheduleOnce(CC_SCHEDULE_SELECTOR(Schedule::myonecschedule), 2);//一次性定时器,第一个参数是一个回掉函数,第二个参数表示在几秒后触发
	
	/*使用回掉函数的帧定时器,功能等同于scheduleUpdate(),区别在于功能可以自定义*/
	schedule(CC_SCHEDULE_SELECTOR(Schedule::myonecschedule));//每帧执行一次
	//schedule(CC_SCHEDULE_SELECTOR(Schedule::myonecschedule),3);//每3秒执行一次
	//schedule(CC_SCHEDULE_SELECTOR(Schedule::myonecschedule), 1, 10, 4);
	//第一次四秒后执行,之后每个1秒执行一次,持续十次,共执行11次

	Size visible = Director::getInstance()->getWinSize();
	Sprite* bullet = Sprite::create("bullet.png");
	bullet->setPosition(visible.width/2-50, visible.height/2-50);
	bullet->setAnchorPoint(Vec2(0, 0));
	bullet->setTag(100);
	addChild(bullet);

	return true;
}

Scene* Schedule::createscene()
{
	Scene* scene = Scene::create();
	Schedule* layer = Schedule::create();
	//layer->setPosition(Vec2(-400, 0));
	scene->addChild(layer);
	return scene;
}

/*帧循环定时器的虚函数,需要重写*/
void Schedule::update(float dt)
{
	static int i = 0;
	if (i == 120)
	{
		unscheduleUpdate();
	}
	i++;
	CCLOG("%g", dt);
}

/*这个dt代表定时的时间*/
void Schedule::myonecschedule(float dt)
{
	static int count = 0;
	count++;
	Size visible = Director::getInstance()->getWinSize();
	float speed = 200 / 2;
	Sprite* bullet= dynamic_cast<Sprite*>(getChildByTag(100));//子类父类之间的转化
	static bool flag = true;
	if (bullet->getPositionX() >= visible.width / 2 - 50 + speed*2 || bullet->getPositionX() <= visible.width / 2 - 50)
	{
		flag = !flag;
	}
	if (flag == true)
	{
		bullet->setPositionX(bullet->getPositionX() + speed * dt);
	}
	else
	{
		bullet->setPositionX(bullet->getPositionX() - speed * dt);
	}
	if (count == 8*60)
	{
		unschedule(CC_SCHEDULE_SELECTOR(Schedule::myonecschedule));//卸载一个定时器函数
	}
}