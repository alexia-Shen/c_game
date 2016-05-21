// Game.h
// CPlusPlusQuest (A2 Sample Solution)
// Created by Peter Hoghton on 28/04/2016

#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <string>
#include <vector>
#include "Enemy.h"
#include "Event.h"

using namespace std;

class Room {

private:

	int row;
	int column;
	vector<Enemy* > enemies;
	vector<Event* > events;
	Room* east;
	Room* west;
	Room* north;
	Room* south;

	bool visited;

	void fillEnemis();
	void setRow(int r);
	void setColumn(int c);



public:
	Room();
	Room(int c, int r);
	void setEast(Room* target);
	void setWest(Room* target);
	void setNorth(Room* target);
	void setSouth(Room* target);

	void setVisited(bool v);

	Room* getEast();
	Room* getWest();
	Room* getNorth();
	Room* getSouth();
	int getRow();
	int getColumn();
	bool getVisited();

	void fillEvent(Event* e);
	bool allWall();

	
};

#endif