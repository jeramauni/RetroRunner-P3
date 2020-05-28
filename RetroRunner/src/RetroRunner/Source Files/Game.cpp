#include <WEManager.h>
#include "Game.h"

#include <CEGUI/CEGUI.h>
#include <Utilities/Vector4.h>

Game Game::instance;

Game::Game() {
	_weM = new WEManager();
	changeScene = false;
	fromNivel = false;
	generateScene = Escenas::None;
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
	if (changeScene) {
		changeScene = false;
		switch (generateScene) {
		case Escenas::MainMenu:
			if (fromNivel) {
				fromNivel = false;
				_weM->popScene();
			}
			GenerateMenuScene();
			break;
		case Escenas::Nivel:
			GenerateMainScene();
			break;
		case Escenas::Pause:
			GeneratePauseScene();
			break;
		case Escenas::Restart:
			_weM->restart();
			break;
		default:
			break;
		}
	}
	return _weM->update();
}

void Game::GenerateMainScene() {
	_weM->setGUIVisible(false);
	// Generamos la escena
	_weM->generateScene("nivel1", Vector4{ 0.2, 0.0, 0.2, 0.8 });
}

void Game::GenerateMenuScene() {
	_weM->generateScene("menu", Vector4{ 0.8, 0.8, 0.8, 0.8 });

	_weM->setGUIVisible(true);
	_weM->loadLayout("EmptyWindow");

	// Añadir a los botones los eventos correspondientes
	_weM->createButton("TaharezLook/Button", "PlayButton", "PLAY", { 0.4f, 0.3f, 0.1f, 0.2f }, { 0.0, 0.0 ,0.0 ,0.0 });
	_weM->addEventToButton("PlayButton", &Game::EventStart);
	_weM->createButton("TaharezLook/Button", "ExitButton", "EXIT", { 0.4f, 0.5f, 0.1f, 0.2f }, { 0.0, 0.0 ,0.0 ,0.0 });
	_weM->addEventToButton("ExitButton", &Game::EventEnd);
}

void Game::GeneratePauseScene() {
	_weM->setGUIVisible(true);
	_weM->loadLayout("EmptyWindow");

	// Añadir a los botones los eventos correspondientes
	_weM->createButton("TaharezLook/Button", "ContinueButton", "CONTINUE", { 0.4f, 0.2f, 0.1f, 0.2f }, { 0.0, 0.0 ,0.0 ,0.0 });
	_weM->addEventToButton("ContinueButton", &Game::EventContinue);
	_weM->createButton("TaharezLook/Button", "MainMenuButton", "MAIN MENU", { 0.4f, 0.4f, 0.1f, 0.2f }, { 0.0, 0.0 ,0.0 ,0.0 });
	_weM->addEventToButton("MainMenuButton", &Game::EventMainMenu);
	_weM->createButton("TaharezLook/Button", "ResetButton", "RESET LV", { 0.4f, 0.6f, 0.1f, 0.2f }, { 0.0, 0.0 ,0.0 ,0.0 });
	_weM->addEventToButton("ResetButton", &Game::EventRestart);
}

void Game::EventContinue() {
	instance._weM->setGUIVisible(false);
	instance._weM->switchComponentsState();
}

void Game::EventMainMenu() {
	instance.changeScene = true;
	instance.fromNivel = true;
	instance.generateScene = Escenas::MainMenu;
}

void Game::EventRestart() {
	instance._weM->setGUIVisible(false);
	instance.changeScene = true;
	instance.generateScene = Escenas::Restart;
}

void Game::EventEnd() {
	instance._weM->close();
}

void Game::EventStart() {
	instance.changeScene = true;
	instance.generateScene = Escenas::Nivel;
}