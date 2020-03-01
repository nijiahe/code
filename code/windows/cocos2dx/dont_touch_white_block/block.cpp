#include "block.h"
#include "Gamelayer.h"


bool block::init(Color3B color, Size size, Vec2 position, __String str, float strsize, Color3B strcolor)
{
	if (!Sprite::init())
	{
		return false;
	}
	Size visible = Director::getInstance()->getWinSize();
	this->setPosition(position);
	this->setContentSize(size);
	this->setTextureRect(Rect(0, 0, size.width - 2, size.height - 2));
	this->setAnchorPoint(Vec2(0, 0));
	this->setColor(color);

	Label * label = Label::createWithTTF(str.getCString(), "fonts/arial.ttf", strsize);
	label->setPosition(size.width*0.5, size.height*0.5);
	label->setAnchorPoint(Vec2(0.5, 0.5));
	label->setColor(strcolor);
	this->addChild(label);

	return true;
}

void block::runtouch()
{
	EventListenerTouchOneByOne* mylistener = EventListenerTouchOneByOne::create();//创建一个触摸监听
	mylistener->setSwallowTouches(false);//设置是否吞噬触摸

	mylistener->onTouchBegan = [=](Touch* touch, Event* event) mutable//指按下时
	{
		Point locationInNode = dynamic_cast<Gamelayer*>(getParent())->convertToNodeSpace(touch->getLocation());
		if (this->getBoundingBox().containsPoint(locationInNode) &&
			(this->getColor() == Color3B::BLACK || this->getColor() == Color3B::YELLOW|| this->getColor() == Color3B::GREEN))
		{
			if (this->getColor() == Color3B::YELLOW)
			{
				dynamic_cast<Gamelayer*>(this->getParent())->run_schedule();
			}
			if (this->getColor() == Color3B::GREEN)
			{
				dynamic_cast<Gamelayer*>(this->getParent())->add_game_end_menu();
				dynamic_cast<Gamelayer*>(this->getParent())->stop_schedule();
			}
			else
			{
				movedown_all();
				dynamic_cast<Gamelayer*>(this->getParent())->runtouch_nextline(this->getPositionY());
				if (dynamic_cast<Gamelayer*>(this->getParent())->line_count >= 40)
				{
					if (!dynamic_cast<Gamelayer*>(this->getParent())->isover)
					{
						dynamic_cast<Gamelayer*>(this->getParent())->auto_add(Gamelayer::block_type::gameover_block);
						dynamic_cast<Gamelayer*>(this->getParent())->isover = !dynamic_cast<Gamelayer*>(this->getParent())->isover;
					}

				}
				else
				{
					dynamic_cast<Gamelayer*>(this->getParent())->add_block_line();
				}
				dynamic_cast<Gamelayer*>(this->getParent())->autoshrink_blockvector();
			}
		}
		return true;
	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(mylistener, this);
}

void block::movedown()
{
	Size visible = Director::getInstance()->getWinSize();
	this->setPosition(this->getPositionX(), this->getPositionY() - visible.height * 0.25);
}

void block::movedown_all()
{
	Gamelayer* layer = dynamic_cast<Gamelayer*>(this->getParent());
	for (Vector<block*>::iterator iwalk = layer->block_vector.begin();
		iwalk != layer->block_vector.end();
		iwalk++)
	{
		((block*)*iwalk)->movedown();
	}
}


block* block::create(Color3B color, Size size, Vec2 position, __String str, float strsize, Color3B strcolor)
{
	block * pRet = new block();
	if (pRet&&pRet->init(color, size, position, str, strsize))
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