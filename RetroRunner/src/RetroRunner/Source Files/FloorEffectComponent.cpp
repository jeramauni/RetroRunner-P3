#include "FloorEffectComponent.h"

#include <iostream>
#include <Container.h>
#include <Messages_defs.h>
#include <PhysicsComponent.h>
#include <ComponentFactory.h>
#include <Utilities/Vector3.h>

CREATE_REGISTER(FloorEffect);

FloorEffectComponent::FloorEffectComponent(Container* e) : CollisionEffectComponent(e)
{
	_name = "FloorEffect";
	effectTime = 0;
}
