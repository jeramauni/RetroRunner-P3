#include "ShurikenSpinComponent.h"
#include <ComponentFactory.h>
#include <PhysicsComponent.h>
#include <Container.h>
#include <Messages_defs.h>
CREATE_REGISTER(ShurikenSpin);
ShurikenSpinComponent::ShurikenSpinComponent(Container* e)
{
	_name = "ShurikenSpin";
	_parent = e;
}

void ShurikenSpinComponent::Init(std::unordered_map<std::string, std::string>& param)
{
	_pc = static_cast<PhysicsComponent*>(_parent->getComponent("Physics"));
	setUpdate();
}

void ShurikenSpinComponent::doEffect()
{

	//RESET DEL MAPA-> En su momento, GUI de victoria y transición al menu principal.
	_parent->getWEManager()->popScene();
	_parent->getWEManager()->setGUIVisible(true);
}


void ShurikenSpinComponent::update(Container* c, float time)
{
	_parent->getNode()->yaw(Ogre::Radian(speed_side), Ogre::Node::TS_LOCAL);
	if (_pc->isColliding()) {
		doEffect();
	}
}
