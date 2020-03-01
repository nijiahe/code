#include "Schedule.h"

bool Schedule::init()
{
	if (!Layer::init())
	{
		return false;
	}

	/************************/
	//��ʱ�����õ�ʵ�ʶ���_scheduler->schedule
	/************************/

	//scheduleUpdate();//����֡ѭ����ʱ�� ���Զ�����ÿִ֡��һ��override��update����

	/*typedef��define���CCRef.h*/
	//scheduleOnce(CC_SCHEDULE_SELECTOR(Schedule::myonecschedule), 2);//һ���Զ�ʱ��,��һ��������һ���ص�����,�ڶ���������ʾ�ڼ���󴥷�
	
	/*ʹ�ûص�������֡��ʱ��,���ܵ�ͬ��scheduleUpdate(),�������ڹ��ܿ����Զ���*/
	schedule(CC_SCHEDULE_SELECTOR(Schedule::myonecschedule));//ÿִ֡��һ��
	//schedule(CC_SCHEDULE_SELECTOR(Schedule::myonecschedule),3);//ÿ3��ִ��һ��
	//schedule(CC_SCHEDULE_SELECTOR(Schedule::myonecschedule), 1, 10, 4);
	//��һ�������ִ��,֮��ÿ��1��ִ��һ��,����ʮ��,��ִ��11��

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

/*֡ѭ����ʱ�����麯��,��Ҫ��д*/
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

/*���dt����ʱ��ʱ��*/
void Schedule::myonecschedule(float dt)
{
	static int count = 0;
	count++;
	Size visible = Director::getInstance()->getWinSize();
	float speed = 200 / 2;
	Sprite* bullet= dynamic_cast<Sprite*>(getChildByTag(100));//���ุ��֮���ת��
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
		unschedule(CC_SCHEDULE_SELECTOR(Schedule::myonecschedule));//ж��һ����ʱ������
	}
}