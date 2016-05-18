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

using namespace std;

class Game {
private:
	static Game* newGame;
	vector<vector<Room* > > map;
public:
	Game();
	static Game* createNewGame();
	void fillMap(int roomSize);
	void fillRow(int roomSize, vector<Room* > &row, vector<Room* > &lastRow);
	void printMap();

};
#endif