#pragma once
#include <CollisionEffectComponent.h>

class MovingAnclaEffectComponent : public CollisionEffectComponent
{
public:
	MovingAnclaEffectComponent(Container* e);
	~MovingAnclaEffectComponent() {};

	void update(Container* c, float time);

private:
	bool dir = true;
};

