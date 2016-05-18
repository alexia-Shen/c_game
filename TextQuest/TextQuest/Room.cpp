// Character.cpp
// CPlusPlusQuest (A2 Sample Solution)
// Created by Peter Hoghton on 22/04/2016

#include "Room.h"
#include "EnemyFactory.h"


Room::Room()
{
	east = NULL;
	west = NULL;
	north = NULL;
	south = NULL;
	fillEnemis();
}
void Room::setEast(Room* room)
{
	east = room;
}

void Room::setWest(Room* room)
{
	west = room;
}
void Room::setNorth(Room* room)
{
	north = room;
}
void Room::setSouth(Room* room)
{
	south = room;
}

Room* Room::getEast()
{
	return east;
}
Room* Room::getWest()
{
	return west;
}
Room* Room::getNorth()
{
	return north;
}
Room* Room::getSouth()
{
	return south;
}

void Room::fillEnemis()
{
	int numEnemies = rand() % 3;
	for (int i = 0; i < numEnemies; i++) {
		enemies.push_back(EnemyFactory::getInstance()->makeEnemy());
	}
}
void Room::fillEvent(Event* e)
{
	events.push_back(e);
}


