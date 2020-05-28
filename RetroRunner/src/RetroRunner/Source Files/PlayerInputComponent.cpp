#include "PlayerInputComponent.h"

//#include <iostream>

#include <Utilities/Vector3.h>
#include <Messages_decl.h>
#include <Messages_defs.h>

//#include <PhysicsComponent.h>
#include "Container.h"
#include "ComponentFactory.h"

#include <iostream>
#include <string>

CREATE_REGISTER(PlayerInput);

PlayerInputComponent::PlayerInputComponent(Container* e) : InputComponent(e) {
    _listener = new PlayerInputListener(e);
    _name = "Player" + _name;
    _parent->getWEManager()->addKeyListener(_listener, _name);
}

void PlayerInputComponent::Init(std::unordered_map<std::string, std::string>& param) {
    
}

void PlayerInputComponent::receive(Container* c, const msg::Message& msg) {
    switch (msg.type_) {
    case msg::SWITCH_COMP:
        _parent->activeComponent(_name);
        break;
    case msg::SCENE_OVER:
        _parent->getWEManager()->removeKeyListener(_name);
        break;
    default:
        break;
    }
}

PlayerInputListener* PlayerInputComponent::getKeyListener() {
    return _listener;
}

InputMouseListener* PlayerInputComponent::getMouseListener(){
    return nullptr;
}

//-----------------------LISTENER-------------------------
PlayerInputListener::PlayerInputListener(Container* ow) {
    _owner = ow;
}

PlayerInputListener::~PlayerInputListener() {}

bool PlayerInputListener::keyPressed(const OIS::KeyEvent& ke) {
    if (_owner->hasComponent("PlayerInput")) {
        switch (ke.key) {
        case OIS::KC_W:
            //std::cout << "Adelante\n";
            _owner->localSend(this, msg::Move(msg::Player, msg::Broadcast, Vector3(1, 0, 0)));
            break;
        case OIS::KC_S:
            //std::cout << "Atras\n";
            _owner->localSend(this, msg::Move(msg::Player, msg::Broadcast, Vector3(-1, 0, 0)));
            break;
        case OIS::KC_A:
            //std::cout << "Izquierda\n"; 
            _owner->localSend(this, msg::Move(msg::Player, msg::Broadcast, Vector3(0, 0, -1)));
            break;
        case OIS::KC_D:
            //std::cout << "Derecha\n";
            _owner->localSend(this, msg::Move(msg::Player, msg::Broadcast, Vector3(0, 0, 1)));
            break;
        case OIS::KC_SPACE:
            //std::cout << "Barra Espaciadora\n";
            _owner->localSend(this, msg::Jump(msg::Player, msg::Broadcast, Vector3(0, 2000, 0)));
            break;
        default:
            break;
        }
    }
    return true;
}

bool PlayerInputListener::keyReleased(const OIS::KeyEvent& ke) {
    if (_owner->hasComponent("PlayerInput")) {
        switch (ke.key) {
        case OIS::KC_W:
            //std::cout << "Adelante back\n";
            _owner->localSend(this, msg::Move(msg::Player, msg::Broadcast, Vector3(-1, 0, 0)));
            break;
        case OIS::KC_S:
            //std::cout << "Atras\n";
            _owner->localSend(this, msg::Move(msg::Player, msg::Broadcast, Vector3(1, 0, 0)));
            break;
        case OIS::KC_A:
            //std::cout << "Izquierda\n";
            _owner->localSend(this, msg::Move(msg::Player, msg::Broadcast, Vector3(0, 0, 1)));
            break;
        case OIS::KC_D:
            //std::cout << "Derecha\n";
            _owner->localSend(this, msg::Move(msg::Player, msg::Broadcast, Vector3(0, 0, -1)));
            break;
        default:
            break;
        }
    }
    return true;
}