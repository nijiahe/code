#include "myLabel.h"

bool myLabel::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}
	
	Size visible = Director::getInstance()->getWinSize();
	
	/*�ѱ��������*/
	/*LabelTTF* ttf = LabelTTF::create("SCORE", "Courier",20);
	ttf->setPosition(visible.width / 2, visible.height / 2);
	addChild(ttf);
	ttf->setFontFillColor(Color3B(0, 0, 0), true);
	ttf->setFontName("Courier New");
	ttf->setFontSize(50);
	ttf->setString("score");*/
	
	/*��������*/
	/*LabelAtlas* atlas = LabelAtlas::create("0","fonts/Labelatlas.png",24,32,'0');
	atlas->setPosition(visible.width / 2, visible.height / 2);
	atlas->setTag(atlastag);
	atlas->setAnchorPoint(Vec2(0.5, 0.5));
	addChild(atlas);
	schedule(SEL_SCHEDULE(&myLabel::myschedule), 1);*/
	
	/*
	Label* ttflb = Label::createWithTTF("SCORE", "fonts/arial.ttf", 50);
	ttflb->setPosition(visible.width / 2, visible.height / 2);
	addChild(ttflb);
	ttflb->setTextColor(Color4B(255, 0, 255, 255));//�����ı���ɫ
	ttflb->enableShadow(Color4B(0, 0, 255, 255), Size(20, -20), 0);//������Ӱ
	ttflb->enableOutline(Color4B(0, 0, 255, 255), 5); //��������������ɫ������һ����ɫ����������������ϸ���˷���ֻ������TTF��������
	ttflb->enableGlow(Color4B(0, 0, 0, 255)); //�����ı�������ɫ��ֻ������TTF�����
	*/

	/*Label* atlas = Label::createWithCharMap("fonts/Labelatlas.png", 24, 32, '0');//����һ��Atlas���� ����һ���Զ��������Ӧ��ͼƬ�ļ������������Զ��������Ӧ��ͼƬ�ļ�����������ÿ���ַ��Ŀ�ȣ���������ÿ���ַ��ĸ߶ȣ������ı�ʾ��ʼ�ַ���
	atlas->setString("0");
	atlas->setPosition(visible.width / 2, visible.height / 2);
	addChild(atlas);
	atlas->setTag(atlastag);
	schedule(SEL_SCHEDULE(&myLabel::myschedule), 1);*/

	/*����취�̳���BatchNode,ͼƬ�е�ÿ���ֶ�������һ��������ص���BatchNode��*/
	Label* bmfont = Label::createWithBMFont("fonts/bitmapFontTest.fnt", "WORLD OF WARCRAFT");
	bmfont->setPosition(visible.width / 2, visible.height/2);
	bmfont->setAnchorPoint(Vec2(0.5, 0.5));
	bmfont->setScale(0.5);
	addChild(bmfont);
	srand(time(0));
	for (int i = 0; i < bmfont->getStringLength(); i++)
	{
		Sprite* spr = bmfont->getLetter(i);
		if (spr)
		{
			spr->setPosition(CCRANDOM_0_1()*visible.width, CCRANDOM_0_1()*visible.height);
		}
		
	}
	float mid = (bmfont->getStringLength() + 1) / 2;
	for (int i = 0; i < bmfont->getStringLength(); i++)
	{
		Sprite* spr = bmfont->getLetter(i);
		if (spr)
		{
			MoveTo* move = MoveTo::create(2, Vec2(visible.width / 2 + (i+1 - mid) * 30, visible.height / 2));
			spr->runAction(move);
		}
	}
	
	


	return true;
}

Scene* myLabel::createscene()
{
	Scene* scene = Scene::create();
	myLabel* layer = myLabel::create();
	scene->addChild(layer, 100);

	return scene;
}

void myLabel::myschedule(float dt)
{
	static int num = 0;
	num += (int)dt;
	std::string res;
	std::stringstream ss;
	ss << num;
	res = ss.str();
	Label* atlas = dynamic_cast<Label*>(getChildByTag(atlastag));
	atlas->setString(res);
	
}
