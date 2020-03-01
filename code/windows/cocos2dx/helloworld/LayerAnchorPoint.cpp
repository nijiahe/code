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
	//spr->setAnchorPoint(Vec2(0.5f, 0.5f));//����������ê������Ϊ���ͼ����0,0��
	spr->setPosition(Vec2(visible.width / 2, visible.height / 2));
	addChild(spr);
	//spr->setScale(2);
	DrawNode* drawnode = DrawNode::create();
	this->addChild(drawnode);
	drawnode->drawSegment(Vec2(0, visible.height/2), Vec2(visible.width, visible.height/2), 1, Color4F(1, 0, 0, 1));
	drawnode->drawSegment(Vec2(visible.width/2, 0), Vec2(visible.width/2, visible.height), 1, Color4F(1, 0, 0, 1));

	//ÿ�������һ�ε�һ�������ṩ�ĺ���,��һ����������Ϊ�ص�����,�ڶ�����������ÿ����ѭ��һ��


	schedule(schedule_selector(LayerAnchorPoint::mySchedule), 1);
	return true;
}

Scene* LayerAnchorPoint::createscene()
{
	Scene* scene = Scene::create();
	LayerAnchorPoint* anchorpoint = LayerAnchorPoint::create();
	//anchorpoint->ignoreAnchorPointForPosition(false);
	//anchorpoint->setPosition(100, 100);
	//ƽʱ����ĺڿ���scene
	//ignore����ʱê��0,0;posiion 0,0��scene��Layer��ȫ�غ�
	//ignore=falseʱê��0.5,0.5;position 0,0 ����Layer�ĵ�һ���޷Ž���scene��
	//Layer����һ������Ļһ����С�ľ���,
	//���ǽ�Layer����scene,�ٽ�sprite����Layer
	//LayerĬ��ignore AnchorPoint
	//��Ĭ��ê��Ϊ0.5,0.5,ignoreʱΪ0
	//��ô��Layer����sceneʱ�������0��0��
	//Ĭ�ϼ���sceneʱ������position����positionΪ0��0
	//��positionΪ���������������Ķ�Ӧ��
	//AnchorPointΪҪ���������������Ķ�Ӧ��
	scene->addChild(anchorpoint);
	return scene;
}
/*
void LayerAnchorPoint::mydraw()
{
	Size visible = Director::getInstance()->getWinSize();
	Color4B(255, 0, 0, 255);//RGB��͸����
	//�˰汾��ccDrawLine��DrawPrimitives::drawLine��������,ʹ��DrawNode�еķ���
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