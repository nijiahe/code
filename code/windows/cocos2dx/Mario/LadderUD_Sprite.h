#ifndef __LadderUD_Sprite_H__
#define __LadderUD_Sprite_H__

#include "Common.h"
#include "Organism.h"
#include "Ladder_Base.h"

class LadderUD_Sprite:public Ladder_Base
{
public:
	CREATE_FUNC(LadderUD_Sprite);
	bool init();

	virtual void auto_move(float t);
	virtual void died_monitor(float t);
	virtual void start_monitor();
	virtual void stop_monitor();
};

#endif