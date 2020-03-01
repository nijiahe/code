#ifndef __Flower_H__
#define __Flower_H__

#include "Common.h"
#include "Organism.h"

class Flower:public Organism
{
public:
	CREATE_FUNC(Flower);
	bool init();

	virtual void birth(Vec2 vec);
	virtual void auto_move(float t);
	virtual void set_picture();
	virtual void set_physics();
	virtual void start_monitor();
	virtual void stop_monitor();
	virtual void clean();
	
	void resume_automove();

	bool _is_up = false;
	float _up_depth = 0;
};

#endif