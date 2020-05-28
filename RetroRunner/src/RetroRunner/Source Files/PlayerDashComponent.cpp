#include "PlayerDashComponent.h"

#include <iostream>
#include <Container.h>
#include <Messages_defs.h>
#include <PhysicsComponent.h>
#include <Utilities/Vector3.h>
#include <ComponentFactory.h>

CREATE_REGISTER(PlayerDash);

PlayerDashComponent::PlayerDashComponent(Container* e)
{
	_name = "PlayerDash";
	_parent = e;
}

void PlayerDashComponent::receive(Container* c, const msg::Message& _msg)
{
	switch (_msg.type_) {
	case msg::HABILITY: {
		const msg::Hability _m = static_cast<const msg::Hability&>(_msg);
		if (!dashInCoolDown) { 
			visionAngle = _parent->getNode()->getOrientation().getYaw().valueDegrees();
			if (visionAngle > 0) visionAngle = abs(visionAngle - 360);
			else visionAngle = abs(visionAngle);
			visionAngle = visionAngle / (180.0 / 3.141592653589793238463);
			_parent->localSend(this, msg::Jump(msg::Player, msg::Broadcast, Vector3(50000 * (cos(visionAngle - (3.14 / 2))), 0, 50000 * (sin(visionAngle - (3.14 / 2))))));
			dashInCoolDown = true;
		}
		break;
	}
	case msg::COLISION: {
		const msg::Colision _m = static_cast<const msg::Colision&>(_msg);
		if (_m._type == "FloorEffect") {
			if (_m._doIt) {
				dashInCoolDown = false; 
			}
		}
		break;
	}
	default:
		break;
	}
}
