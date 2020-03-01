#include "DotLine.h"
#include "CommonAlgorithm.h"

bool DotLine::init() {
	if (!DrawNode::init()) {
		return false;
	}

	return true;
}

void DotLine::drawDotLine(int dotLength, int gap, Vec2 origin, Vec2 destination,Color4F c) {//由用户保证origin在destination的左下区域
	float x = destination.x - origin.x;
	float y = destination.y - origin.y;

	float x_origin = origin.x;
	float y_origin = origin.y;

	float total_length = MyMath::Sqrt(x*x +y*y);
	float dot_x = dotLength * x / total_length;
	float dot_y = dotLength * y / total_length;

	float gap_x = gap * x / total_length;
	float gap_y = gap * y / total_length;

	bool choose_x = (x > y);
	if (choose_x) {
		while (x_origin < destination.x) {
			drawLine(Vec2(x_origin, y_origin), Vec2(x_origin + dot_x, y_origin + dot_y), c);
			x_origin += dot_x + gap_x;
			y_origin += dot_y + gap_y;
		}
	}
	else {
		while (y_origin < destination.y) {
			drawLine(Vec2(x_origin, y_origin), Vec2(x_origin + dot_x, y_origin + dot_y), c);
			x_origin += dot_x + gap_x;
			y_origin += dot_y + gap_y;
		}
	}
	
}
