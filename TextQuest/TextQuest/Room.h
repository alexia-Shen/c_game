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
	vector<Enemy* > enemies;
	vector<Event* > events;
	Room* east;
	Room* west;
	Room* north;
	Room* south;
	void fillEnemis();


public:
	Room();
	void setEast(Room* target);
	void setWest(Room* target);
	void setNorth(Room* target);
	void setSouth(Room* target);
	Room* getEast();
	Room* getWest();
	Room* getNorth();
	Room* getSouth();

	void fillEvent(Event* e);

	
};

#endif