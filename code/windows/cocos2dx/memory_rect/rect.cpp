#include "rect.h"
#include "gamelayer.h"
#include "cocos-ext.h"//cocos2dx扩展头文件
#include "SimpleAudioEngine.h"
USING_NS_CC_EXT;
using namespace CocosDenshion;

bool rect::init()
{
	if (!Sprite::initWithFile("rect.png"))
	{
		return false;
	}
	setContentSize(Size(30, 30));
	setAnchorPoint(Vec2(0, 0));
	scheduleOnce(SEL_SCHEDULE(&rect::scheduleruntouch), 3);
	
	return true;
}

void rect::runtouch()
{
	Size visible = Director::getInstance()->getWinSize();
	this->mylistener = EventListenerTouchOneByOne::create();//创建一个触摸监听
	mylistener->setSwallowTouches(false);//设置是否吞噬触摸
	mylistener->onTouchBegan = [=](Touch* touch, Event* event) mutable//指按下时
	{ 
		Point locationInNode = dynamic_cast<gamelayer *>(getParent())->convertToNodeSpace(touch->getLocation());
		Rect ccrect = Rect(this->getPositionX()-getAnchorPoint().x*getContentSize().width,
			this->getPositionY()- getAnchorPoint().y*getContentSize().height,
			this->getContentSize().width,
			this->getContentSize().height);
		if (ccrect.containsPoint(locationInNode))
		{
			if (this->num != -1)
			{
				if (!this->ison)
				{
					if (dynamic_cast<gamelayer *>(getParent())->OKnum != this->num)
					{
						//输了
						dynamic_cast<gamelayer *>(getParent())->errnonum++;		
						SimpleAudioEngine::getInstance()->playEffect("sound/game_over.wav");
						dynamic_cast<gamelayer *>(getParent())->lostresolution();
					}
					else
					{
						dynamic_cast<gamelayer *>(getParent())->OKnum++;
						SimpleAudioEngine::getInstance()->playEffect("sound/achievement.wav");
						shownum();
						dynamic_cast<gamelayer *>(getParent())->winresolution();
					}		
				}
			}
			else
			{
				dynamic_cast<gamelayer *>(getParent())->errnonum++;
				dynamic_cast<gamelayer *>(getParent())->lostresolution();
				dynamic_cast<gamelayer *>(getParent())->closealltouch();
			}
		}
		
		return true;//返回值决定消息是否要发到别的touch函数
	};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(mylistener, this);
}

void rect::shownum()
{
	std::string res;
	std::stringstream ss;
	ss << num;
	res = ss.str();
	Label* ttflb = Label::createWithTTF(res, "fonts/arial.ttf", getContentSize().width);
	ttflb->setPosition(getContentSize().width/2, getContentSize().height/2);
	addChild(ttflb);
	ttflb->setTag(ttflbtag);
	ison = !ison;
}
void rect::hidenum()
{
	Label* rect = dynamic_cast<Label*>(getChildByTag(ttflbtag));
	if (rect != nullptr)
	{
		rect->removeFromParent();
		ison = !ison;
	}
}

void rect::scheduleruntouch(float dt)
{
	runtouch();
}

void rect::closetouch()
{
	mylistener->onTouchBegan = [=](Touch* touch, Event* event) mutable//指按下时
	{
		return true;//返回值决定消息是否要发到别的touch函数
	};
}