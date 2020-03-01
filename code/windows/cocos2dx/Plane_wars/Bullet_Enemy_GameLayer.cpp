#include "Bullet_Enemy_GameLayer.h"

#include "MainGameLayer.h"
#include "plane.h"
#include "Bullet2.h"
#include  "Plane_GameLayer.h"

bool Bullet_Enemy_GameLayer::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 0)))
	{
		return false;
	}
	run_remove_bullet_schedule();

	return true;
}

void Bullet_Enemy_GameLayer::add_bullet(Bullet2 * bullet)
{
	bullet_vector.pushBack(bullet);
	addChild(bullet);
}

void Bullet_Enemy_GameLayer::remove_bullet_schedule_callback(float t)
{
	for (int i = 0; i < bullet_vector.size(); i++)
	{
		if (bullet_vector.at(i)->out_of_visible())
		{
			bullet_vector.at(i)->removeFromParent();
			bullet_vector.erase(i);
		}
		else if (bullet_vector.at(i)->is_hit_plane())
		{
			bullet_vector.at(i)->removeFromParent();
			bullet_vector.erase(i);
			dynamic_cast<MainGameLayer *>(getParent())->_Plane_Layer->_plane->injured();
		}
	}
}

void Bullet_Enemy_GameLayer::run_remove_bullet_schedule()
{
	schedule(SEL_SCHEDULE(&Bullet_Enemy_GameLayer::remove_bullet_schedule_callback));
}

