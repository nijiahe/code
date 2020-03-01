#ifndef _Common_H__
#define _Common_H__

#include "cocos2d.h"

USING_NS_CC;

#include "cocos-ext.h"//cocos2dx扩展头文件
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
using namespace extension;

#define Winsize Director::getInstance()->getWinSize()

class Common 
{
public:
	enum Action_Tag{Move_Left,Move_Right,God_Action};
	enum Tile_Type{Coin,Solid_Block,Tub_Block,Pipe,Flagpole,Land,Ladder,None};
	enum Face_dir{Left,Right};
	enum{Rounds};
	static Tile_Type Convert_Gid_To_Type(int gid)
	{
		if (gid == 22 * 30 + 1 || gid == 22 * 30 + 2 || gid == 22 * 30 + 3 || gid == 23 * 30 + 1 || gid == 23 * 30 + 2 || gid == 23 * 30 + 3 || gid == 24 * 30 + 1 || gid == 24 * 30 + 2 || gid == 24 * 30 + 3)
		{
			return Coin;
		}
		else if (
			gid == 0 * 30 + 2 || gid == 0 * 30 + 3 || gid == 0 * 30 + 7 ||
			gid == 1 * 30 + 1 || gid == 1 * 30 + 2 || gid == 1 * 30 + 3 ||
			gid == 2 * 30 + 1 || gid == 2 * 30 + 2 || gid == 2 * 30 + 3 ||
			gid == 3 * 30 + 2 || gid == 3 * 30 + 3 ||
			gid == 5 * 30 + 1 || gid == 5 * 30 + 2 || gid == 5 * 30 + 3 ||
			gid == 20 * 30 + 1 || gid == 20 * 30 + 2 || gid == 20 * 30 + 3 ||
			gid == 21 * 30 + 1 || gid == 21 * 30 + 2 || gid == 21 * 30 + 3||
			gid == 17 * 30 + 24 || gid == 17 * 30 + 26 || gid == 17 * 30 + 28 || gid == 17 * 30 + 30)
		{
			return Solid_Block;
		}
		else if (gid == 0 * 30 + 1 || gid == 3 * 30 + 1 )
		{
			return Tub_Block;
		}
		else if (gid == 0 * 30 + 24 || gid == 0 * 30 + 25 || gid == 0 * 30 + 29 || gid == 0 * 30 + 30 ||
			gid == 1 * 30 + 24 || gid == 1 * 30 + 25 || gid == 1 * 30 + 29 || gid == 1 * 30 + 30 ||
			gid == 2 * 30 + 24 || gid == 2 * 30 + 25 || gid == 2 * 30 + 29 || gid == 2 * 30 + 30 ||
			gid == 3 * 30 + 24 || gid == 3 * 30 + 25 || gid == 3 * 30 + 29 || gid == 3 * 30 + 30 ||
			gid == 4 * 30 + 24 || gid == 4 * 30 + 25 || gid == 4 * 30 + 29 || gid == 4 * 30 + 30 ||
			gid == 5 * 30 + 24 || gid == 5 * 30 + 25 || gid == 5 * 30 + 29 || gid == 5 * 30 + 30 ||
			gid == 6 * 30 + 24 || gid == 6 * 30 + 25 || gid == 6 * 30 + 29 || gid == 6 * 30 + 30 ||
			gid == 7 * 30 + 24 || gid == 7 * 30 + 25 || gid == 7 * 30 + 29 || gid == 7 * 30 + 30 ||
			gid == 8 * 30 + 24 || gid == 8 * 30 + 25 || gid == 8 * 30 + 29 || gid == 8 * 30 + 30 ||
			gid == 9 * 30 + 24 || gid == 9 * 30 + 25 || gid == 9 * 30 + 29 || gid == 9 * 30 + 30 ||
			gid == 2 * 30 + 22 || gid == 2 * 30 + 23 || gid == 2 * 30 + 27 || gid == 2 * 30 + 28 ||
			gid == 3 * 30 + 22 || gid == 3 * 30 + 23 || gid == 3 * 30 + 27 || gid == 3 * 30 + 28 ||
			gid == 7 * 30 + 22 || gid == 7 * 30 + 23 || gid == 7 * 30 + 27 || gid == 7 * 30 + 28 ||
			gid == 8 * 30 + 22 || gid == 8 * 30 + 23 || gid == 8 * 30 + 27 || gid == 8 * 30 + 28)
		{
			return Pipe;
		}
		else if (
			gid == 14 * 30 + 24 || gid == 14 * 30 + 26 || gid == 14 * 30 + 28 || gid == 14 * 30 + 30 || 
			gid == 15 * 30 + 24 || gid == 15 * 30 + 26 || gid == 15 * 30 + 28 || gid == 15 * 30 + 30 ||
			gid == 16 * 30 + 24 || gid == 16 * 30 + 26 || gid == 16 * 30 + 28 || gid == 16 * 30 + 30) 
		{
			return Flagpole;
		}
		else if (
			gid == 4 * 30 + 1 || gid == 4 * 30 + 2 || gid == 4 * 30 + 3||
			gid == 8 * 30 + 1 || gid == 8 * 30 + 2 || gid == 8 * 30 + 3 || 
			gid == 11 * 30 + 7 || gid == 11 * 30 + 8 || gid == 11 * 30 + 9 ||
			gid == 9 * 30 + 1 || gid == 9 * 30 + 2 || gid == 9 * 30 + 6 || gid == 9 * 30 + 7 || gid == 9 * 30 + 8 ||
			gid == 10 * 30 + 1 || gid == 10 * 30 + 2 ||
			gid == 11 * 30 + 1 || gid == 11 * 30 + 2 || 
			gid == 12 * 30 + 1 || gid == 12 * 30 + 2 || 
			gid == 13 * 30 + 1 || gid == 13 * 30 + 2 || 
			gid == 14 * 30 + 1 || gid == 14 * 30 + 2 || 
			gid == 15 * 30 + 1 || gid == 15 * 30 + 2 )
		{
			return Land;
		}
		else
		{
			return None;
		}
	}

	static Animation * createAnimation(char * filename, int start, int end, int width, float delay,char * key)
	{
		Texture2D* texture = Director::getInstance()->getTextureCache() ->addImage(filename);
		Vector<SpriteFrame *> sprframe_vec;
		for (int i = start; i <= end; i++)
		{
			SpriteFrame * sprframe = SpriteFrame::createWithTexture(texture, Rect(i*width, 0, width, texture->getContentSize().height));
			sprframe_vec.pushBack(sprframe);
		}
		Animation * animation = Animation::createWithSpriteFrames(sprframe_vec, delay);
		AnimationCache::getInstance()->addAnimation(animation, key);
		return animation;
	}

	static void MoveNode(Node * node, Vec2 vec)
	{
		node->setPosition(node->getPosition() + vec);
	}
	static char * format(char * str1 = "", int num = 0, char * str2 = "")
	{
		static char buf[2048];
		sprintf(buf, "%s%d%s", str1, num, str2);
		return buf;
	}
	static Scene * createscene(Layer * layer)
	{
		Scene * scene = Scene::create();
		scene->addChild(layer);
		return scene;
	}
	static void log_position(Vec2 position)
	{
		CCLOG("%g %g", position.x, position.y);
	}
	static void log_size(Size size)
	{
		CCLOG("%g %g", size.width, size.height);
	}
	static void log_rect(Rect rect)
	{
		CCLOG("%g %g %g %g", rect.getMinX(), rect.getMinY(), rect.size.width, rect.size.height);
	}
};


#endif