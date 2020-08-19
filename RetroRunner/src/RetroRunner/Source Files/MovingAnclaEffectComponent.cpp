#include "MovingAnclaEffectComponent.h"

#include <iostream>
#include <Container.h>
#include <Messages_defs.h>
#include <PhysicsComponent.h>
#include <ComponentFactory.h>
#include <Utilities/Vector3.h>

CREATE_REGISTER(MovingAnclaEffect);

MovingAnclaEffectComponent::MovingAnclaEffectComponent(Container* e) : CollisionEffectComponent(e)
{
	_name = "MovingAnclaEffect";
}

void MovingAnclaEffectComponent::update(Container* c, float time)
{
	if (_pc->position().z > 2400 && dir) dir = false;
	else if(_pc->position().z < 1850 && !dir) dir = true;

	if(dir)_pc->move(Vector3(0, 0, 10));
	else _pc->move(Vector3(0, 0, -10));

	if (_pc->isColliding() && !buffActive)
	{
		doEffect();
		buffActive = true;
		startTime = clock(); //Start timer
	}
	if (buffActive)
	{
		secondsPassed = (clock() - startTime) / CLOCKS_PER_SEC;
		if (secondsPassed >= effectTime)
		{
			secondsPassed = 0;
			buffActive = false;
			undoEffect();
		}
	}
}