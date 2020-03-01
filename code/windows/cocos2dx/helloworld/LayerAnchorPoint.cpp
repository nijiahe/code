#include "LayerAnchorPoint.h"
#include<stdio.h>
LayerAnchorPoint* LayerAnchorPoint::create()
{
	LayerAnchorPoint* pRet = new LayerAnchorPoint();
	if (pRet&&pRet->init())
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


bool LayerAnchorPoint::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visible = Director::getInstance()->getWinSize();

	spr = Sprite::create("anchor3.png");
	//spr->setAnchorPoint(Vec2(0.5f, 0.5f));//将这个精灵的锚点设置为这个图案的0,0点
	spr->setPosition(Vec2(visible.width / 2, visible.height / 2));
	addChild(spr);
	//spr->setScale(2);
	DrawNode* drawnode = DrawNode::create();
	this->addChild(drawnode);
	drawnode->drawSegment(Vec2(0, visible.height/2), Vec2(visible.width, visible.height/2), 1, Color4F(1, 0, 0, 1));
	drawnode->drawSegment(Vec2(visible.width/2, 0), Vec2(visible.width/2, visible.height), 1, Color4F(1, 0, 0, 1));

	//每两秒调用一次第一个参数提供的函数,第一个参数意义为回调函数,第二个参数表述每几秒循环一次


	schedule(schedule_selector(LayerAnchorPoint::mySchedule), 1);
	return true;
}

Scene* LayerAnchorPoint::createscene()
{
	Scene* scene = Scene::create();
	LayerAnchorPoint* anchorpoint = LayerAnchorPoint::create();
	//anchorpoint->ignoreAnchorPointForPosition(false);
	//anchorpoint->setPosition(100, 100);
	//平时输出的黑框是scene
	//ignore插入时锚点0,0;posiion 0,0及scene和Layer完全重合
	//ignore=false时锚点0.5,0.5;position 0,0 及将Layer的第一象限放进了scene中
	//Layer就是一个和屏幕一样大小的精灵,
	//我们将Layer加入scene,再将sprite加入Layer
	//Layer默认ignore AnchorPoint
	//及默认锚点为0.5,0.5,ignore时为0
	//那么将Layer加入scene时对齐的是0，0点
	//默认加入scene时不设置position，及position为0，0
	//及position为被插入事物的事物的对应点
	//AnchorPoint为要插入别的事物的事物的对应点
	scene->addChild(anchorpoint);
	return scene;
}
/*
void LayerAnchorPoint::mydraw()
{
	Size visible = Director::getInstance()->getWinSize();
	Color4B(255, 0, 0, 255);//RGB，透明度
	//此版本中ccDrawLine和DrawPrimitives::drawLine都被废弃,使用DrawNode中的方法
	//DrawNode::dra(Vec2(0, visible.width / 2), Vec2(visible.height, visible.width / 2));
	//DrawPrimitives::drawLine(Vec2(visible.height / 2, 0), Vec2(visible.height / 2, visible.width));
	DrawNode
}
*/

void LayerAnchorPoint::mySchedule(float dt)
{
	static float ro = 0;
	ro += 6;
	spr->setRotation(ro);
}