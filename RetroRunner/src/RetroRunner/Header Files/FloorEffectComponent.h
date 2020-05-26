#pragma once
#include <CollisionEffectComponent.h>

class FloorEffectComponent : public CollisionEffectComponent {
public:
	FloorEffectComponent(Container* e);
	~FloorEffectComponent() {};
};

