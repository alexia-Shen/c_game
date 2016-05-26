// Game.h
// CPlusPlusQuest (A2 Sample Solution)
// Created by Peter Hoghton on 28/04/2016

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include <sstream>
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
	void locatePlayer(Player* p, int positionX = -1, int positionY = -1);
	void playerMove(char dir);
	void setCheatMode();
	bool getCheatMode();
	bool checkRoom();
	void fight();
	void executeEvents();
	void useItem();
	void setPlayer(Player* p);

	void saveGame();
	void saveMap();
	void saveInventory();
	bool loadMap(string mapOwner);
	void loadEvents();
	void loadInventory();

	Player* getPlayer();
};
#endif