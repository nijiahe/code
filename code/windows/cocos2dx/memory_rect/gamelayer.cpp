#include "gamelayer.h"
#include "rect.h"
#include "lostlayer.h"
#include "winlayer.h"
#include "cocos-ext.h"//cocos2dx扩展头文件
#include "SimpleAudioEngine.h"
USING_NS_CC_EXT;
using namespace CocosDenshion;

bool gamelayer::init(int count)
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 0)))
	{
		return false;
	}
	putindifferentnum(count);
	preparerect();
	num_in_rect();
	Size visible = Director::getInstance()->getWinSize();
	showall(0);
	maketimeschedule();//在上方有一个倒数3 2 1 0的time计时器
	scheduleOnce(SEL_SCHEDULE(&gamelayer::hideall), 3);

	return true;
}

Scene* gamelayer::createscene(int count)
{
	Scene* scene = Scene::create();
	gamelayer* layer = gamelayer::create(count);
	scene->addChild(layer);
	return scene;
}

gamelayer* gamelayer::create(int count)
{
	gamelayer* pRet = new gamelayer();
	if (pRet&&pRet->init(count))
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

void gamelayer::putindifferentnum(int count)
{
	srand(time(0));
	while (1)
	{
		if (numvec.size() == count)
		{
			break;
		}
		int num = rand()%49;
		std::vector<int>::iterator iwalk = numvec.begin();
		for (; iwalk != numvec.end(); iwalk++)
		{
			if (*iwalk == num)
			{
				break;
			}
		}
		if (iwalk == numvec.end())
		{
			numvec.push_back(num);
		}
	}
}

void gamelayer::preparerect()
{
	Size visible = Director::getInstance()->getWinSize();
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			rect* rec = rect::create();
			rec->setPosition(visible.width / 2 + (j + 1 - 4) * 31, visible.height*0.15 + 31 * i);
			rec->setAnchorPoint(Vec2(0.5, 0.5));
			addChild(rec);
			rectvec.push_back(rec);
		}
	}
	
}

void gamelayer::num_in_rect()
{
	std::vector<int>::iterator iwalk = numvec.begin();
	int i = 0;
	for (; iwalk != numvec.end(); iwalk++,i++)
	{
		int n = (int)*iwalk;
		rectvec[n]->num = i;
	}
}

void gamelayer::showall(float dt)
{
	std::vector<int>::iterator iwalk = numvec.begin();
	for (; iwalk != numvec.end(); iwalk++)
	{

		rectvec[(int)*iwalk]->shownum();
	}
}

void gamelayer::hideall(float dt)
{
	std::vector<int>::iterator iwalk = numvec.begin();
	for (; iwalk != numvec.end(); iwalk++)
	{
		rectvec[(int)*iwalk]->hidenum();
	}
}

void gamelayer::maketimeschedule()
{
	Size visible = Director::getInstance()->getWinSize();
	Label* atlas = Label::createWithCharMap("fonts/Labelatlas.png", 24, 32, '0');//创建一个Atlas对象， 参数一是自定义字体对应的图片文件，参数二是自定义字体对应的图片文件，参数二是每个字符的宽度，参数三是每个字符的高度，参数四表示起始字符。
	atlas->setString("3");
	atlas->setPosition(visible.width / 2, visible.height *0.8);
	addChild(atlas);
	atlas->setTag(atlastag);
	atlas->setContentSize(Size(0.15*visible.width,0.15*visible.height));
	schedule(SEL_SCHEDULE(&gamelayer::timeschedule), 1);
}

void gamelayer::timeschedule(float dt)
{
	this->scheduletime -= (int)dt;
	std::string res;
	std::stringstream ss;
	Label* atlas = dynamic_cast<Label*>(getChildByTag(atlastag));
	if (this->scheduletime >= 0)
	{
		ss << this->scheduletime;
		res = ss.str();
		atlas->setString(res);
	}
}


void gamelayer::winresolution()
{
	if (iswin())
	{
		winlayer* layer = winlayer::create();
		addChild(layer);
		this->closealltouch();
	}
}
void gamelayer::lostresolution()
{
	if (islost())
	{
		showall(0);
		lostlayer* layer = lostlayer::create();
		addChild(layer);
		this->closealltouch();
	}
}

bool gamelayer::iswin()
{
	if (this->OKnum >= (int)numvec.size())
	{
		return true;
	}
	return false;
}
bool gamelayer::islost()
{
	if (this->errnonum >= 1)
	{
		return true;
	}
	return false;
}

void gamelayer::closealltouch()
{
	std::vector<rect*>::iterator iwalk = rectvec.begin();
	for (; iwalk != rectvec.end(); iwalk++)
	{
		((rect*)*iwalk)->closetouch();
	}
}