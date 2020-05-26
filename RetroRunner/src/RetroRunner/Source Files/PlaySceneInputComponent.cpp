#include "PlaySceneInputComponent.h"

#include <Container.h>
#include <Messages_defs.h>
#include <ComponentFactory.h>

#include "Game.h"

CREATE_REGISTER(PlaySceneInput);

PlaySceneInputComponent::PlaySceneInputComponent(Container* e) : InputComponent(e){
    _listener = new WEInputListener(e);
    _name = "PlayScene" + _name;
    _parent->getWEManager()->addKeyListener(_listener, _name);
}

void PlaySceneInputComponent::Init(std::unordered_map<std::string, std::string>& param) {}

// Cuando reacciona al teclado
WEInputListener* PlaySceneInputComponent::getKeyListener() {
    return _listener;
}

// Cuando reacciona al raton
InputMouseListener* PlaySceneInputComponent::getMouseListener() {
    return nullptr;
}

////-----------------------LISTENER-------------------------
WEInputListener::WEInputListener(Container* ow) {
    _owner = ow;
}

WEInputListener::~WEInputListener() {}

bool WEInputListener::keyPressed(const OIS::KeyEvent& ke) {
    switch (ke.key) {
    case OIS::KC_ESCAPE:
        _owner->globalSend(this, msg::SwitchComp(msg::None, msg::Broadcast));
        if (_owner->getWEManager()->getGUIvis()) {
            _owner->getWEManager()->setGUIVisible(false);
        }
        else {
            Game::instance.GeneratePauseScene();
        }
        break;
    default:
        break;
    }

    return true;
}

bool WEInputListener::keyReleased(const OIS::KeyEvent& ke) {
    return true;
}