#include <WEManager.h>
//#include <Scene.h>

#include "Game.h"

Game::Game() {
	_weM = new WEManager();
}

Game::~Game() {
	delete _weM;
}

void Game::Init() {
	// Iniciamos el gm
	_weM->Init();
	
	GenerateMainScene();
}

bool Game::update() {
	return _weM->update();
}

void Game::GenerateMainScene() {
	// Generamos la escena
	_weM->generateScene("map.txt");

	// Colocamos la camara
	_weM->moveCam("MainCam", 250, 400, -700);
	_weM->camLookAt("MainCam", 250, 0, 0);
	_weM->rotateCam("MainCam", 1, 0, 0, 180);
}
