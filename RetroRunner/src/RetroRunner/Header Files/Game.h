#ifndef GAME_H
#define GAME_H

#pragma once

class WEManager;

class Game {
public:
	Game();
	~Game();

	void Init();
	bool update();

	static Game instance;
	void GenerateMainScene();
	void GenerateMenuScene();
	void GeneratePauseScene();

private:
	WEManager* _weM;


	//Eventos
	static void EventEnd();
	static void EventStart();
	static void EventContinue();
	static void EventMainMenu();
};
#endif