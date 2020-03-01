#include "Loading_Layer.h"
#include "Start_Layer.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;//SimpleAudioEngine声音文件的命名空间



bool Loading_Layer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//背景
	Sprite * spr = Sprite::create("BackGround/background.png");
	spr->setPosition(Winsize.width*0.5, Winsize.height*0.5);
	spr->setContentSize(Size(Winsize.width, Winsize.height));
	addChild(spr);

	//进度条轨道
	Sprite * process_track = Sprite::create("UI/sliderTrack.png");
	addChild(process_track);
	process_track->setPosition(Winsize.width*0.5, Winsize.height*0.2);
	//进度条
	Sprite * process_timer_spr = Sprite::create("UI/sliderProgress.png");
	_process_timer = ProgressTimer::create(process_timer_spr);
	addChild(_process_timer);
	_process_timer->setType(ProgressTimer::Type::BAR);
	_process_timer->setMidpoint(Vec2(0, 0));
	_process_timer->setBarChangeRate(Vec2(1, 0));
	_process_timer->setPercentage(0);
	_process_timer->setPosition(Winsize.width*0.5, Winsize.height*0.2);
	//loading .字样label
	_loading_label = Label::createWithTTF("loading .","fonts/arial.ttf",20);
	_loading_label->setColor(Color3B(0, 0, 0));
	_loading_label->setAnchorPoint(Vec2(0, 0.5));
	_loading_label->setPosition(Winsize.width*0.5 - _loading_label->getContentSize().width, Winsize.height*0.2 + 20);
	addChild(_loading_label);

	//进度条读数label
	_process_label = Label::createWithTTF("0", "fonts/arial.ttf", 20);
	_process_label->setColor(Color3B(0, 0, 0));
	_process_label->setPosition(Winsize.width*0.5+ _process_label->getContentSize().width*0.5+30, Winsize.height*0.2 + 20);
	addChild(_process_label);

	schedule(SEL_SCHEDULE(&Loading_Layer::loading_label_monitor),0.5f);
	schedule(SEL_SCHEDULE(&Loading_Layer::process_label_monitor));
	loading_source();
	
	

	return true;
}


void Loading_Layer::loading_source()
{
	int picfilecount = sizeof(picfile) / sizeof(*picfile);
	int musicfilecount = sizeof(music_file) / sizeof(*music_file);

	_total_file_num = picfilecount;
	
	//加载音乐
	for (int i = 0; i < musicfilecount; ++i)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(music_file[i]);
	}
	//加载动画
	Common::createAnimation("Player_and_Monster/smallWalkLeft.png", 0, 9, 14, 0.05f, "red_small_mario_move_left");
	Common::createAnimation("Player_and_Monster/smallWalkRight.png", 0, 9, 14, 0.05f, "red_small_mario_move_right");
	Common::createAnimation("Player_and_Monster/small_die.png", 0, 6, 16, 0.2f, "red_small_mario_died");

	Common::createAnimation("Player_and_Monster/walkLeft.png", 0, 9, 18, 0.05f, "red_Big_mario_move_left");
	Common::createAnimation("Player_and_Monster/walkRight.png", 0, 9, 18, 0.05f, "red_Big_mario_move_right");
	Common::createAnimation("Player_and_Monster/normal_die.png", 0, 6, 16, 0.2f, "red_Big_mario_died");
	
	Common::createAnimation("Player_and_Monster/Mushroom0.png", 0, 1, 16, 0.25f, "Mushroom_move_left");
	Common::createAnimation("Player_and_Monster/Mushroom0.png", 1, 0, 16, 0.25f, "Mushroom_move_right");
	Common::createAnimation("Player_and_Monster/Mushroom0.png", 2, 3, 16, 0.25f, "Mushroom_died");

	Common::createAnimation("Player_and_Monster/tortoise0.png", 2, 3, 18, 0.25f, "Tortoise_move_left");
	Common::createAnimation("Player_and_Monster/tortoise0.png", 4, 5, 18, 0.25f, "Tortoise_move_right");
	Common::createAnimation("Player_and_Monster/tortoise0.png", 8, 9, 18, 0.25f, "Tortoise_died");

	Common::createAnimation("Player_and_Monster/flower0.png", 0, 1, 16, 0.25f, "Flower_move");

	Common::createAnimation("Player_and_Monster/flyFishLeft.png", 0, 1, 16, 0.25f, "flyfish_move_left0");
	Common::createAnimation("Player_and_Monster/flyFishRight.png", 0, 1, 16, 0.25f, "flyfish_move_right0");
	Common::createAnimation("Player_and_Monster/flyFishLeft.png", 2, 3, 16, 0.25f, "flyfish_move_left1");
	Common::createAnimation("Player_and_Monster/flyFishRight.png", 2, 3, 16, 0.25f, "flyfish_move_right1");
	Common::createAnimation("Player_and_Monster/flyFishLeft.png", 4, 5, 16, 0.25f, "flyfish_move_left2");
	Common::createAnimation("Player_and_Monster/flyFishRight.png", 4, 5, 16, 0.25f, "flyfish_move_right2");
	
	Common::createAnimation("Player_and_Monster/boss.png", 0, 3, 32, 0.25f, "Boss_move_left");
	Common::createAnimation("Player_and_Monster/boss.png", 4, 7, 32, 0.25f, "Boss_move_right");
	//初始化随机数
	srand(time(NULL));
	//AnimationCache::getInstance()->addAnimation()

	//加载图片
	for (int i = 0; i < _total_file_num; ++i)
	{
		Director::getInstance()->getTextureCache()->addImageAsync(picfile[i], CC_CALLBACK_1(Loading_Layer::loadImageCallBack, this));
	}
}

void Loading_Layer::loadImageCallBack(Texture2D* pic)
{
	_process_timer->setPercentage(_process_timer->getPercentage()+100/ _total_file_num);
}

void Loading_Layer::loading_label_monitor(float t)
{
	static int loading_num = 0;
	if (loading_num == 0)
	{
		_loading_label->setString("loading .");
	}
	else if (loading_num == 1)
	{
		_loading_label->setString("loading ..");
	}
	else if (loading_num == 2)
	{
		_loading_label->setString("loading ...");
	}
	loading_num++;
	if (loading_num >= 3)
	{
		loading_num = 0;
	}
}

void Loading_Layer::process_label_monitor(float t)
{
	int num = (int)_process_timer->getPercentage();
	_process_label->setString(Common::format("", num, "%"));
	if (100 == _process_timer->getPercentage())
	{
		replacescene_Start_Layer();
	}
}


void Loading_Layer::replacescene_Start_Layer()
{
	Director::getInstance()->replaceScene(Common::createscene(Start_Layer::create()));
}