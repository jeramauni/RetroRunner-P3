#pragma once
#include <Component.h> 

class Container;

class PlayerDashComponent : public Component
{
public:
	PlayerDashComponent(Container* e);
	~PlayerDashComponent() {}; 
	void Init(std::unordered_map<std::string, std::string>& param) {};
	void update(Container* c, float time) {};

	//Receive implementation
	void receive(Container* c, const msg::Message& _msg);

private:
	bool dashInCoolDown = false;
	float visionAngle = 0;
};

