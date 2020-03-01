#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

#define Winsize Director::getInstance()->getWinSize()
#define __kindsOfMechanism 1
#define __kindOfModel 2
#define __designEdgeGap 20
#define __designContentGap 2
#define __designLRratio (1.0f/3)
#define __designDisplayWidthGap 80
#define __designDisplayHeightGap 100
#define __devided 10
#define __MaxYear 100
#define __Chinese_TTF "fonts/FZLiuGQKSJW.TTF"
#define __Chinese_XML "strings.xml"


class Common
{
public:
	inline static Vec2 log_position(Vec2 position)
	{
		CCLOG("%g %g", position.x, position.y);
		return position;
	}
	inline static Size log_size(Size size)
	{
		CCLOG("%g %g", size.width, size.height);
		return size;
	}
	inline static Rect log_rect(Rect rect)
	{
		CCLOG("%g %g %g %g", rect.getMinX(), rect.getMinY(), rect.size.width, rect.size.height);
		return rect;
	}
	inline static void setConstentSize_comparedWithAnother(Node* compared_node,Node* change_node,float xratio=1,float yratio=1) {
		change_node->setContentSize(Size(compared_node->getContentSize().width * xratio, compared_node->getContentSize().height * yratio));
	}
	inline static Vec2 shift(Vec2 origin, float shift_x, float shift_y) {
		return Vec2(origin.x + shift_x, origin.y + shift_y);
	}
};
