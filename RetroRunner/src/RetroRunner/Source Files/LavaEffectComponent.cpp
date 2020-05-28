#include "LavaEffectComponent.h"

#include <iostream>
#include <Container.h>
#include <Messages_defs.h>
#include <PhysicsComponent.h>
#include <ComponentFactory.h>
#include <Utilities/Vector3.h>

CREATE_REGISTER(LavaEffect);

LavaEffectComponent::LavaEffectComponent(Container* e) {
	_name = "LavaEffect";
	_parent = e;
}

void LavaEffectComponent::Init(std::unordered_map<std::string, std::string>& param) {
	_pc = static_cast<PhysicsComponent*>(_parent->getComponent("Physics"));

	setUpdate();
}

void LavaEffectComponent::update(Container* c, float time) {
	if (_pc->isColliding())	{
		doEffect();
	}
}

void LavaEffectComponent::doEffect() {
	_parent->globalSend(this, msg::Colision(msg::Player, msg::Broadcast, _name, true));
}
