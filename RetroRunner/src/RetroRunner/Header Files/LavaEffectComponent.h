#pragma once
#include <Component.h>
#include <cstdlib>

class Container;
class Vector3;
class PhysicsComponent;

class LavaEffectComponent : public Component {
public:
	LavaEffectComponent(Container* e);
	~LavaEffectComponent() {};
	void Init(std::unordered_map<std::string, std::string>& param);

	void update(Container* c, float time);
	
	void doEffect();
	void undoEffect();

	void receive(Container* c, const msg::Message& _msg) {};

protected:
	PhysicsComponent* _pc;
};

