#include "rect.h"
#include "gamelayer.h"
#include "cocos-ext.h"//cocos2dx��չͷ�ļ�
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
	this->mylistener = EventListenerTouchOneByOne::create();//����һ����������
	mylistener->setSwallowTouches(false);//�����Ƿ����ɴ���
	mylistener->onTouchBegan = [=](Touch* touch, Event* event) mutable//ָ����ʱ
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
						//����
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
		
		return true;//����ֵ������Ϣ�Ƿ�Ҫ�������touch����
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
	mylistener->onTouchBegan = [=](Touch* touch, Event* event) mutable//ָ����ʱ
	{
		return true;//����ֵ������Ϣ�Ƿ�Ҫ�������touch����
	};
}