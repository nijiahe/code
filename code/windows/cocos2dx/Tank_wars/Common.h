#ifndef __Common_H__
#define __Common_H__

#include "cocos2d.h"
USING_NS_CC;

#define Winsize Director::getInstance()->getWinSize()

class Common
{
public:
	enum Dir_Control{Up, Right,Down,Left};
	enum TileType { NONE, BLOCK, STEEL, HOME,RIVER};
	enum Enemy_Tank_Type{Red_panzer,Green_panzer,Red_speed_tank,Green_speed_tank,Red_normal_tank,White_normal_tank};
	enum Item_Type{active, bomb, mintank, star, steel, timer};

	static TileType getTileType(int gid)
	{
		if (gid == 5 || gid == 6 || gid == 11 || gid == 12)
			return STEEL;
		if (gid == 13 || gid == 14 || gid == 19 || gid == 20)
			return BLOCK;
		if (gid == 17 || gid == 18 || gid == 23 || gid == 24)
			return HOME;
		if (gid == 15 || gid == 16 || gid == 21 || gid == 22)
			return RIVER;

		return NONE;
	}
	static void moveNodeX(Node* n, int dx)
	{
		n->setPositionX(n->getPositionX() + dx);
	}
	static void moveNodeY(Node* n, int dy)
	{
		n->setPositionY(n->getPositionY() + dy);
	}

	static Scene * createscene(Layer * layer)
	{
		Scene * scene = Scene::create();
		scene->addChild(layer);
		return scene;
	}

	static char * format(char * str1 = "", int num=0, char * str2 = "")
	{
		static char format_str[100];
		sprintf(format_str, "%s%d%s", str1, num, str2);
		return format_str;
	}
	static void log_size(Size size)
	{
		CCLOG("%g %g", size.width, size.height);
	}
	static void log_point(Vec2 point)
	{
		CCLOG("%g %g", point.x, point.y);
	}
};

#endif