#ifndef __Chess_Color_H__
#define __Chess_Color_H__

class Chess_Color
{
public:
	enum Holder_Color
	{
		red,
		black,
	};
	Chess_Color(Holder_Color color);
	Chess_Color();
	int _color;

	bool operator ==(Chess_Color other);
};

#endif