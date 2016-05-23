// Character.cpp
// CPlusPlusQuest (A2 Sample Solution)
// Created by Peter Hoghton on 22/04/2016

#include "Room.h"
#include "EnemyFactory.h"


Room::Room()
{
	row = 0;
	column = 0;
	east = NULL;
	west = NULL;
	north = NULL;
	south = NULL;
	fillEnemis();
}

Room::Room(int c, int r)
{
	row = r;
	column = c;
	east = NULL;
	west = NULL;
	north = NULL;
	south = NULL;
	visited = false;
	fillEnemis();
}
//setter and getter
void Room::setRow(int r)
{
	row = r;
}

void Room::setColumn(int c)
{
	column = c;
}

void Room::setVisited(bool v)
{
	visited  = v;
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

int Room::getRow()
{
	return row;
}

int Room::getColumn()
{
	return column;
}

bool Room::getVisited()
{
	return visited;
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

bool Room::allWall()
{
	return (east == NULL && west == NULL && north == NULL && south == NULL);
}

vector<Enemy* > Room::getEnemies()
{
	return enemies;
}

vector<Event* > Room::getEvents()
{
	return events;
}


