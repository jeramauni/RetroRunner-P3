#include "PlayerMoveComponent.h"

#include <iostream>
#include <Container.h>
#include <Messages_defs.h>
#include <PhysicsComponent.h>
#include <ComponentFactory.h>

CREATE_REGISTER(PlayerMove);

PlayerMoveComponent::PlayerMoveComponent(Container* e) {
	_name = "PlayerMove";
	_parent = e;
}

void PlayerMoveComponent::Init(std::unordered_map<std::string, std::string>& param) {
	_pc = static_cast<PhysicsComponent*>(_parent->getComponent("Physics"));
}

void PlayerMoveComponent::receive(Container* c, const msg::Message& _msg)
{
	switch (_msg.type_)
	{
	case msg::MOVE: {
		const msg::Move _m = static_cast<const msg::Move&>(_msg);
		_pc->move(_m._dir);

		break;
	}
	case msg::JUMP: {
		const msg::Jump _m = static_cast<const msg::Jump&>(_msg);
		_pc->jump(_m._dir);
		//jump(_m._dir);
		break;
	}
	default:
		break;
	}
}
