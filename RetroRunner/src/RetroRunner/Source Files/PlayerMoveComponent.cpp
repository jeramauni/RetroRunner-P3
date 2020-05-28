#include "PlayerMoveComponent.h"

#include <Container.h>
#include <Messages_defs.h>
#include <PhysicsComponent.h>
#include <ComponentFactory.h>
#include <Utilities/Vector3.h>

#include <iostream>

CREATE_REGISTER(PlayerMove);

PlayerMoveComponent::PlayerMoveComponent(Container* e) {
	_name = "PlayerMove";
	_parent = e;
	_velocity = new Vector3(0, 0, 0);
}

void PlayerMoveComponent::Init(std::unordered_map<std::string, std::string>& param) {
	_pc = static_cast<PhysicsComponent*>(_parent->getComponent("Physics"));
	setUpdate();
}

void PlayerMoveComponent::update(Container* c, float time) {
	_pc->checkColliding();
	if (std::abs(_pc->linearVelocity().y) > 1.0f) {
		onTheFloor = false;
	}

	if (_pc->position().y < -300) {
		_parent->getWEManager()->restart();
	}

	visionAngle = _parent->getNode()->getOrientation().getYaw().valueDegrees();
	if (visionAngle > 0) visionAngle = abs(visionAngle - 360);
	else visionAngle = abs(visionAngle); 
	visionAngle = visionAngle / (180.0 / 3.141592653589793238463);

	if (*_velocity == Vector3(1, 0, 0)) //ADELANTE
	{
		_pc->move(Vector3(maxVelocity * (cos(visionAngle - (3.14 / 2))), 0, maxVelocity * (sin(visionAngle - (3.14 / 2)))));
	}
	else if (*_velocity == Vector3(1, 0, 1)) //ADELANTE + DERECHA
	{
		_pc->move(Vector3(maxVelocity * (cos(visionAngle - (3.14 / 4))), 0, maxVelocity * (sin(visionAngle - (3.14 / 4)))));
	}
	else if (*_velocity == Vector3(1, 0, -1)) //ADELANTE + IZQUIERDA
	{
		_pc->move(Vector3(-maxVelocity * (cos(visionAngle + (3.14 / 4))), 0, -maxVelocity * (sin(visionAngle + (3.14 / 4)))));
	}
	else if (*_velocity == Vector3(0, 0, 1)) //DERECHA
	{
		_pc->move(Vector3(maxVelocity * (cos(visionAngle)), 0, maxVelocity * (sin(visionAngle))));
	}
	else if (*_velocity == Vector3(-1, 0, 0)) //ATRAS
	{
		_pc->move(Vector3(maxVelocity * (cos(visionAngle + (3.14 / 2))), 0, maxVelocity * (sin(visionAngle + (3.14 / 2)))));
	}
	else if (*_velocity == Vector3(-1, 0, 1)) //ATRAS + DERECHA
	{
		_pc->move(Vector3(maxVelocity * (cos(visionAngle + (3.14 / 4))), 0, maxVelocity * (sin(visionAngle + (3.14 / 4)))));
	}
	else if (*_velocity == Vector3(-1, 0, -1)) //ATRAS + IZQUIERDA
	{
		_pc->move(Vector3(-maxVelocity * (cos(visionAngle - (3.14 / 4))), 0, -maxVelocity * (sin(visionAngle - (3.14 / 4)))));
	}
	else if (*_velocity == Vector3(0, 0, -1)) { //IZQUIERDA
		_pc->move(Vector3(-maxVelocity * (cos(visionAngle)), 0, -maxVelocity * (sin(visionAngle))));
	}
	else {
		_pc->move(Vector3(0, 0, 0));
	}
}

void PlayerMoveComponent::receive(Container* c, const msg::Message& _msg) {
	switch (_msg.type_) {
	case msg::MOVE: {
		const msg::Move _m = static_cast<const msg::Move&>(_msg);
		Vector3 v = _m._dir;
		*_velocity += _m._dir;
		break;
	}
	case msg::JUMP: {
		const msg::Jump _m = static_cast<const msg::Jump&>(_msg);
		if (onTheFloor) {
			_pc->push(_m._dir);
			_parent->localSend(this, msg::PlaySound(msg::None, msg::Broadcast, std::string("jumpSound")));
		}
		else if(_m._dir.y <= 0)
		{
			_pc->push(_m._dir);
		}
		break;
	}
	case msg::COLISION: {
		const msg::Colision _m = static_cast<const msg::Colision&>(_msg);
		if (_m._type == "AnclaEffect") {
			slowedDown = _m._doIt;
			if (slowedDown) maxVelocity = maxVelocity / 2;
			else maxVelocity = maxVelocity * 2;
		}
		else if (_m._type == "JumpEffect") {
			if (slowedDown) {
				_pc->push(Vector3(0, 1000, 0));
			}
		}
		else if (_m._type == "FloorEffect")	{
			if (_m._doIt) onTheFloor = true;
		}
		else if (_m._type == "LavaEffect") {
			_parent->getWEManager()->restart();
		}
		break;
	}
	default:
		break;
	}
}


