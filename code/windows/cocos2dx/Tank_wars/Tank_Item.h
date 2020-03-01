#ifndef __Tank_Item_H__
#define __Tank_Item_H__

#include "Common.h"

class Tank_Item:public Sprite
{
public:
	bool init(Common::Item_Type type);
	static Tank_Item * create(Common::Item_Type type);

	void set_picture(const char* filename);
	

	Common::Item_Type _type;
};

#endif