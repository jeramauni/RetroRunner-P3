#include "PlayerInputComponent.h"

#include <iostream>

#include "Container.h"
#include "ComponentFactory.h"

CREATE_REGISTER(PlayerInput);

PlayerInputComponent::PlayerInputComponent(Container* e) : InputComponent(e) {
    _listener = new PlayerInputListener(e);
    _name = "Player" + _name;
    _parent->getWEManager()->addKeyListener(_listener, _name);
}

void PlayerInputComponent::Init(std::unordered_map<std::string, std::string>& param) {
    
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
    switch (ke.key) {
    case OIS::KC_W:
        std::cout << "Adelante\n";
        //Implementar en cada uno de estos el comportamiento con physics
        //_owner->getComponent("Physics")->moverse(haciaadelante);
        break;
    case OIS::KC_S:
        std::cout << "Atras\n";
        break;
    case OIS::KC_A:
        std::cout << "Izquierda\n";
        break;
    case OIS::KC_D:
        std::cout << "Derecha\n";
        break;
    default:
        break;
    }

    return true;
}

bool PlayerInputListener::keyReleased(const OIS::KeyEvent& ke) {
    return false;
}