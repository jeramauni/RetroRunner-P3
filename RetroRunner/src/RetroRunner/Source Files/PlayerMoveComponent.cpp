#include "PlayerMoveComponent.h"

#include <iostream>
#include <Container.h>
#include <Messages_defs.h>
#include <ComponentFactory.h>

CREATE_REGISTER(PlayerMove);



PlayerMoveComponent::PlayerMoveComponent(Container* e) : PhysicsComponent(e)
{
	_name = "PlayerMove";
}

void PlayerMoveComponent::Init(std::unordered_map<std::string, std::string>& param) {
 
}

void PlayerMoveComponent::receive(Container* c, const msg::Message& _msg)
{
	switch (_msg.type_)
	{
	case msg::MOVE: {
		const msg::Move _m = static_cast<const msg::Move&>(_msg);
		move(_m._dir);
		break;
	}
	default:
		break;
	}
}
