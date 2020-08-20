#pragma once
#include <CollisionEffectComponent.h>

class MovingAnclaEffectComponent : public CollisionEffectComponent
{
public:
	MovingAnclaEffectComponent(Container* e);
	~MovingAnclaEffectComponent() {};

	void update(Container* c, float time);
	void rotateOncePerChange(Container* c);
private:
	bool dir = true;
	bool once = false;
};

