#include "Gamelayer.h"

bool Gamelayer::init()
{
	if (!LayerColor::initWithColor(Color4B(125, 125, 125, 255)))
	{
		return false;
	}
	srand(time(0));
	winsize = Director::getInstance()->getWinSize();
	start_layer_prepare();
	set_timeschedule();
	
	return true;
}

Scene* Gamelayer::createscene()
{
	Scene* scene = Scene::create();
	Gamelayer* layer = Gamelayer::create();
	scene->addChild(layer);
	return scene;
}

void Gamelayer::add_white_block(Vec2 position)
{
	block * white_block = block::create(Color3B::WHITE, Size(winsize.width*0.25, winsize.height*0.25), position );
	addChild(white_block);
	block_vector.pushBack(white_block);
}
void Gamelayer::add_black_block(Vec2 position)
{
	block * black_block = block::create(Color3B::BLACK, Size(winsize.width*0.25, winsize.height*0.25), position );
	addChild(black_block);
	block_vector.pushBack(black_block);
}
void Gamelayer::add_gamestart_block(Vec2 position)
{
	block * gamestart_block = block::create(Color3B::YELLOW, Size(winsize.width, winsize.height*0.25 ), position,"Game Start",30);
	addChild(gamestart_block);
	block_vector.pushBack(gamestart_block);
}
void Gamelayer::add_gameover_block(Vec2 position)
{
	block * gameover_block = block::create(Color3B::GREEN, Size(winsize.width, winsize.height), position, "End", 50);
	addChild(gameover_block);
	block_vector.pushBack(gameover_block);
}

void Gamelayer::auto_add(block_type type)
{
	if (block_vector.size() > 0)
	{
		block * last_block = block_vector.back();

		if (type == white_block)
		{
			if (last_block->getPositionX()+last_block->getContentSize().width <= winsize.width / 4 * 3)
			{
				Vec2 position(last_block->getPositionX() + winsize.width*0.25,
					last_block->getPositionY());
				add_white_block(position);
			}
			else
			{
				Vec2 position(0, last_block->getPositionY()+ winsize.height*0.25);
				add_white_block(position);
			}
		}
		else if (type == black_block)
		{
			if (last_block->getBoundingBox().getMaxX() <= winsize.width / 4 * 3)
			{
				Vec2 position(last_block->getPositionX() + winsize.width*0.25,
					last_block->getPositionY());
				add_black_block(position);
			}
			else
			{
				Vec2 position(0, last_block->getPositionY() + winsize.height*0.25);
				add_black_block(position);
			}
		}
		else if (type == gamestart_block)
		{
			add_gamestart_block(Vec2(0,last_block->getPositionY()+winsize.height*0.25));
		}
		else
		{
			add_gameover_block(Vec2(0, last_block->getPositionY() + winsize.height*0.25));
		}
	}
	else
	{
		if (type == white_block)
		{
			add_white_block(Vec2(0,0));
		}
		else if (type == black_block)
		{
			add_black_block(Vec2(0, 0));
		}
		else if (type == gamestart_block)
		{
			add_gamestart_block(Vec2(0,0));
		}
		else
		{
			add_gameover_block(Vec2(0, 0));
		}
	}
}

void Gamelayer::add_block_line()
{
	int flag = rand() % 4;
	for (int i = 0; i < 4; i++)
	{
		if (i == flag)
		{
			auto_add(black_block);
		}
		else
		{
			auto_add(white_block);
		}
	}
	line_count++;
}

void Gamelayer::start_layer_prepare()
{
	auto_add(gamestart_block);
	block_vector.at(0)->runtouch();
	for (int i = 0; i < 3; i++)
	{
		add_block_line();
	}
}

void Gamelayer::set_timeschedule()
{
	Size visible = Director::getInstance()->getWinSize();
	Label* ttflb = Label::createWithTTF("0", "fonts/arial.ttf", 50);
	ttflb->setLocalZOrder(100);
	ttflb->setString("0");
	ttflb->setColor(Color3B::BLUE);
	ttflb->setPosition(visible.width / 2, visible.height *0.9);
	addChild(ttflb);
	ttflb->setTag(ttflbtag);
}
void Gamelayer::run_schedule()
{
	schedule(SEL_SCHEDULE(&Gamelayer::time_schedule));
}

void Gamelayer::stop_schedule()
{
	this->unschedule(SEL_SCHEDULE(&Gamelayer::time_schedule));
}

void Gamelayer::time_schedule(float dt)
{
	this->schedule_time += dt;
	std::string res;
	std::stringstream ss;
	Label* ttflb = dynamic_cast<Label*>(getChildByTag(ttflbtag));
	ss << (int)(this->schedule_time/0.1)*0.1;
	res = ss.str();
	ttflb->setString(res);
}

void Gamelayer::runtouch_nextline(float height)
{
	for (Vector<block*>::iterator iwalk = this->block_vector.begin();
		iwalk != this->block_vector.end();
		iwalk++)
	{
		if (((block*)*iwalk)->getPositionY() >= height + winsize.height*0.125 &&
			((block*)*iwalk)->getPositionY() <= height + winsize.height*0.375)
		{
			((block*)*iwalk)->runtouch();
		}
	}
}

void Gamelayer::autoshrink_blockvector()
{
	for (int i = 0; i < 5; i++)
	{
		if (block_vector.at(1)->getPositionY() + block_vector.at(1)->getContentSize().height < 0 - winsize.height*0.25)
		{
			block_vector.at(1)->removeFromParent();
			block_vector.eraseObject(block_vector.at(1));
		}
	}
}

void Gamelayer::add_game_end_menu()
{
	MenuItem* quit_menu = MenuItemLabel::create(Label::createWithTTF("Quit", "fonts/arial.ttf", 50), CC_CALLBACK_1(Gamelayer::quit_menu_callback, this));
	MenuItem* play_again_menu = MenuItemLabel::create(Label::createWithTTF("Play Again", "fonts/arial.ttf", 50), CC_CALLBACK_1(Gamelayer::playagain_menu_callback, this));
	Menu * menu = Menu::create(quit_menu, play_again_menu,NULL);
	menu->alignItemsVerticallyWithPadding(winsize.height*0.3);
	addChild(menu);
}

void Gamelayer::quit_menu_callback(Ref* ref)
{
	exit(0);
}
void Gamelayer::playagain_menu_callback(Ref* ref)
{
	Scene * scene = Gamelayer::createscene();
	Director::getInstance()->replaceScene(scene);
}

