#include <Component.h>

class Container;
class Vector3;
class PhysicsComponent;
class ShurikenSpinComponent : public Component {
public:
	ShurikenSpinComponent(Container* e);
	~ShurikenSpinComponent() {};
	void Init(std::unordered_map<std::string, std::string>& param);

	void doEffect();

	void update(Container* c, float time);
	void receive(Container* c, const msg::Message& _msg) {};
private:
	float speed_side = 0.08f;
	PhysicsComponent* _pc;
};