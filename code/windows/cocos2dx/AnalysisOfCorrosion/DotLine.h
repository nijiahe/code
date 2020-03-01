#pragma once

#include "common.h"

class DotLine :public DrawNode {
public:
	CREATE_FUNC(DotLine);
	bool init();

	void drawDotLine(int dotLength,int gap, Vec2 origin, Vec2 destination, Color4F c);
};