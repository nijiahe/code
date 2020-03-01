#include "myLabel.h"

bool myLabel::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}
	
	Size visible = Director::getInstance()->getWinSize();
	
	/*已被声明否决*/
	/*LabelTTF* ttf = LabelTTF::create("SCORE", "Courier",20);
	ttf->setPosition(visible.width / 2, visible.height / 2);
	addChild(ttf);
	ttf->setFontFillColor(Color3B(0, 0, 0), true);
	ttf->setFontName("Courier New");
	ttf->setFontSize(50);
	ttf->setString("score");*/
	
	/*依赖美工*/
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
	ttflb->setTextColor(Color4B(255, 0, 255, 255));//设置文本颜色
	ttflb->enableShadow(Color4B(0, 0, 255, 255), Size(20, -20), 0);//设置阴影
	ttflb->enableOutline(Color4B(0, 0, 255, 255), 5); //设置文言轮廓颜色，参数一是颜色，参数二是线条粗细，此方法只能用在TTF字体的情况
	ttflb->enableGlow(Color4B(0, 0, 0, 255)); //设置文本发光颜色，只能用在TTF情况。
	*/

	/*Label* atlas = Label::createWithCharMap("fonts/Labelatlas.png", 24, 32, '0');//创建一个Atlas对象， 参数一是自定义字体对应的图片文件，参数二是自定义字体对应的图片文件，参数二是每个字符的宽度，参数三是每个字符的高度，参数四表示起始字符。
	atlas->setString("0");
	atlas->setPosition(visible.width / 2, visible.height / 2);
	addChild(atlas);
	atlas->setTag(atlastag);
	schedule(SEL_SCHEDULE(&myLabel::myschedule), 1);*/

	/*这个办法继承了BatchNode,图片中的每个字都被当成一个精灵加载到了BatchNode中*/
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
