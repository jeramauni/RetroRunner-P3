#include "ShurikenSpinComponent.h"
#include <PhysicsComponent.h>
#include <Container.h>

#include "Game.h"

#include <ComponentFactory.h>

CREATE_REGISTER(ShurikenSpin);

ShurikenSpinComponent::ShurikenSpinComponent(Container* e) {
	_name = "ShurikenSpin";
	_parent = e;
}

void ShurikenSpinComponent::Init(std::unordered_map<std::string, std::string>& param) {
	_pc = static_cast<PhysicsComponent*>(_parent->getComponent("Physics"));
	setUpdate();
}

void ShurikenSpinComponent::doEffect() {
	_parent->getWEManager()->popScene();
	Game::instance.GenerateMenuScene();
}


void ShurikenSpinComponent::update(Container* c, float time) {
	_parent->getNode()->yaw(Ogre::Radian(speed_side), Ogre::Node::TS_LOCAL);
	if (_pc->isColliding()) {
		doEffect();
	}
}
