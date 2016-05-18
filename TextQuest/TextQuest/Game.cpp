#include "Room.h"
#include "Player.h"
#include "Event.h"
#include "Game.h"
using namespace std;

Game* Game::newGame = NULL;
Game::Game() {}

Game* Game::createNewGame() {
	return Game::newGame == NULL ? newGame = new Game() : newGame;
}

void Game::fillMap(int roomSize)
{
	for (int j = 0; j < roomSize; j++)
	{
		vector<Room *> temp; 
		if (j>0)
			fillRow(roomSize, temp, vector<Room* >());
		else
			fillRow(roomSize, temp, map[j-1]);	
		map.push_back(temp);
	}
}
void Game::fillRow(int roomSize, vector<Room* > &row, vector<Room* > &lastRow)
{
	for (int i = 0; i < roomSize; i++)
	{
		Room *temp = new Room();
			
		if (i > 0 && i < roomSize -1)
		{
			Room* destination = rand() % 2 == 0 ? NULL : row[i - 1];
			temp->setWest(destination);
			row[i - 1]->setEast(temp->getWest());
		}
		else if (i == roomSize - 1)
		{
			temp->setWest(row[i - 1]->getEast());
		}
		if (!lastRow.empty() || lastRow.size() == 0)
		{
			Room* destination = rand() % 2 == 0 ? NULL : lastRow[i];
			temp->setNorth(destination);
			lastRow[i]->setSouth(temp->getNorth());
		}
		row.push_back(temp);
	}
}

void Game::printMap()
{
}