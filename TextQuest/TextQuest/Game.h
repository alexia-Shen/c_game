// Game.h
// CPlusPlusQuest (A2 Sample Solution)
// Created by Peter Hoghton on 28/04/2016

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <vector>

#include "Enemy.h"
#include "Event.h"
#include "Room.h"
#include "Player.h"

using namespace std;

class Game {
private:
	static Game* newGame;
	vector<vector<Room* > > map;
	vector<string> flogMap;
	Player* player;

	bool cheatMode;
public:
	Game();
	static Game* createNewGame();
	void fillMap(int roomSize);
	void createDoors(int roomSize);
	void printMap();
	void printFlogMap();
	void createFlogMap();
	void createPlayer(int roomSize);
	void playerMove(char dir);
	void setCheatMode();
	bool getCheatMode();
};
#endif