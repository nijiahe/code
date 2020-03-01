#include "Bullet_GameLayer.h"
#include "Plane_GameLayer.h"
#include "MainGameLayer.h"
#include "plane.h"
#include "Bullet1.h"

bool Bullet_GameLayer::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 0)))
	{
		return false;
	}
	prepare_bullet_batchnode();
	start_shoot(0.5f);
	run_remove_bullet_schedule();

	return true;
}

void Bullet_GameLayer::prepare_bullet_batchnode()
{
	/*将这张图片渲染到内存*/
	bullet_batchnode = SpriteBatchNode::create("ui/shoot.png");
	addChild(bullet_batchnode);
}


void Bullet_GameLayer::produce_bullet(float t)
{
	plane * _plane = dynamic_cast<MainGameLayer *>(getParent())->_Plane_Layer->_plane;
	if (_plane != nullptr&&!_plane->is_died())
	{
		Bullet1 * bullet = Bullet1::create();
		bullet->setAnchorPoint(Vec2(0.5, 0));
		bullet->setPosition(_plane->getPositionX(), _plane->getPositionY() + _plane->getBoundingBox().size.height);
		bullet_run(bullet);
		bullet_vector.pushBack(bullet);
		addChild(bullet);
	}
}

void Bullet_GameLayer::bullet_run(Sprite * bullet)
{
	Size visible = Director::getInstance()->getWinSize();
	float t = visible.height / bullet_speed;
	MoveBy * by = MoveBy::create(t, Vec2(0, visible.height));
	bullet->runAction(by);
}


void Bullet_GameLayer::start_shoot(float shoot_rate)
{
	schedule(SEL_SCHEDULE(&Bullet_GameLayer::produce_bullet), shoot_rate);
}

void Bullet_GameLayer::stop_shoot()
{
	unschedule(SEL_SCHEDULE(&Bullet_GameLayer::produce_bullet));
}

void Bullet_GameLayer::remove_bullet_schedule_callback(float t)
{
	for (int i = 0; i < bullet_vector.size(); i++)
	{
		if (bullet_vector.at(i)->out_of_visible())
		{
			bullet_vector.at(i)->removeFromParent();
			bullet_vector.erase(i);
		}
		else if(bullet_vector.at(i)->is_hit_enemy())
		{

		}
	}
}

void Bullet_GameLayer::run_remove_bullet_schedule()
{
	schedule(SEL_SCHEDULE(&Bullet_GameLayer::remove_bullet_schedule_callback));
}
