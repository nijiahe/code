#include "Game_End_Layer.h"
#include "MainGameLayer.h"
#include "Game_Control_layer.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

bool Game_End_Layer::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 0)))
	{
		return false;
	}
	run_add();

	return true;
}

void Game_End_Layer::run_add()
{
	scheduleOnce(SEL_SCHEDULE(&Game_End_Layer::add_callback), 1);
}


void Game_End_Layer::add_callback(float t)
{
	add_Menu();
	add_Score_Label();
	Director::getInstance()->pause();
}

void Game_End_Layer::add_Score_Label()
{
	Size visible = Director::getInstance()->getWinSize();

	Label * score_label = Label::createWithTTF("SCORE", "fonts/arial.ttf",50);
	score_label->setColor(Color3B(143, 146, 147));
	score_label->setPosition(visible.width*0.5, visible.height*0.8);
	addChild(score_label);

	int this_score = dynamic_cast<MainGameLayer *>(getParent())->_Game_Control_layer->score;
	Label * score_num_label = Label::createWithTTF((__String::createWithFormat("%d", this_score))->getCString(), "fonts/arial.ttf", 35);
	score_num_label->setColor(Color3B(143, 146, 147));
	score_num_label->setPosition(visible.width*0.5, visible.height*0.7);
	addChild(score_num_label);

	int highest_score = Update_Highest_Score(this_score);

	Label * highest_score_label = Label::createWithTTF("Highest Score", "fonts/arial.ttf", 50);
	highest_score_label->setColor(Color3B(143, 146, 147));
	highest_score_label->setPosition(visible.width*0.5, visible.height*0.6);
	addChild(highest_score_label);

	Label * score_highest_label = Label::createWithTTF((__String::createWithFormat("%d", highest_score))->getCString(), "fonts/arial.ttf", 35);
	score_highest_label->setColor(Color3B(143, 146, 147));
	score_highest_label->setPosition(visible.width*0.5, visible.height*0.5);
	addChild(score_highest_label);
}

void Game_End_Layer::add_Menu()
{
	Size visible = Director::getInstance()->getWinSize();
	
	MenuItem * item1 = MenuItemFont::create("Play Again", CC_CALLBACK_1(Game_End_Layer::Play_Again_Menu_callback, this));
	item1->setScale(1.5f);
	item1->setColor(Color3B(143, 146, 147));
	
	MenuItem * item2 = MenuItemFont::create("Quit", CC_CALLBACK_1(Game_End_Layer::Quit_callback, this));
	item2->setScale(1.5f);
	item2->setColor(Color3B(143, 146, 147));

	Menu * menu = Menu::create(item1, item2,NULL);
	menu->alignItemsVerticallyWithPadding(0.1*visible.height);
	menu->setPositionY(menu->getPositionY() - 0.2*visible.height);

	addChild(menu);
}

int Game_End_Layer::Update_Highest_Score(int value_num)
{
	int num = -1;
	num = UserDefault::getInstance()->getIntegerForKey("integer");
	if (num == -1|| value_num > num)
	{
		UserDefault::getInstance()->setIntegerForKey("integer", value_num);
		return value_num;
	}
	return num;
}

void Game_End_Layer::Play_Again_Menu_callback(Ref * ref)
{
	Director::getInstance()->resume();
	Scene * scene = MainGameLayer::createscene();
	Director::getInstance()->replaceScene(scene);
}

void Game_End_Layer::Quit_callback(Ref * ref)
{
	Director::getInstance()->end();
}