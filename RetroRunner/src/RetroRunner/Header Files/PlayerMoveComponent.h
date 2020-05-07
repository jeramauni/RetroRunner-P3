#pragma once

#include <PhysicsComponent.h>

class Container;

//InputComponent es la clase base de todos los componentes de Input
class PlayerMoveComponent : public PhysicsComponent {
public:
	PlayerMoveComponent(Container* e);
	~PlayerMoveComponent() {};
	void Init(std::unordered_map<std::string, std::string>& param);

	// Implementar la que sea necesaria
	void update(Container* c, float time) {};

	//Receive implementation
	void receive(Container* c, const msg::Message& _msg);

private:
};