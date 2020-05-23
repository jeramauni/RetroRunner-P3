#include <WEManager.h>
#include "Game.h"

#include <CEGUI/CEGUI.h>

#include <Utilities/Vector4.h>

Game Game::instance;

Game::Game() {
	_weM = new WEManager();
}

Game::~Game() {
	delete _weM;
}

void Game::Init() {
	// Iniciamos el gm
	_weM->Init();
	
	//Escena de menus
	GenerateMenuScene();
}

bool Game::update() {
	if (_weM->update()) 
		return true;
	else 
		return false;
}

void Game::GenerateMainScene() {
	_weM->setGUIVisible(false);
	// Generamos la escena
	_weM->generateScene("map", "entities");
}

void Game::GenerateMenuScene() {
	_weM->generateScene("menu", "entities");
	_weM->setGUIVisible(true);
	_weM->loadLayout("EmptyWindow");

	// A�adir a los botones los eventos correspondientes
	_weM->createButton("TaharezLook/Button", "PlayButton", "PLAY", { 0.4f, 0.3f, 0.1f, 0.2f }, { 0.0, 0.0 ,0.0 ,0.0 });
	_weM->addEventToButton("PlayButton", &Game::EventStart);
	_weM->createButton("TaharezLook/Button", "ExitButton", "EXIT", { 0.4f, 0.5f, 0.1f, 0.2f }, { 0.0, 0.0 ,0.0 ,0.0 });
	_weM->addEventToButton("ExitButton", &Game::EventEnd);
}

void Game::EventEnd() {
	instance._weM->close();
}

void Game::EventStart() {
	instance.GenerateMainScene();
}