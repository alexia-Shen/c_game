#include "Room.h"
#include "Player.h"
#include "Event.h"
#include "Game.h"
#include "Vocation.h"
#include "Player.h"

using namespace std;

Game* Game::newGame = NULL;
Game::Game() { cheatMode = false; }

Game* Game::createNewGame() {
	return Game::newGame == NULL ? newGame = new Game() : newGame;
}

void Game::fillMap(int roomSize)
{
	for (int j = 0; j < roomSize; j++)
	{
		vector<Room* > row;
		for (int i = 0; i < roomSize; i++)
		{
			Room *temp = new Room(i,j);
			row.push_back(temp);
		}
		map.push_back(row);
	}
}

void Game::createDoors(int roomSize)
{
	vector<char> direction;
	vector<Room> temp;

	int startX = rand() % roomSize;
	int startY = rand() % roomSize;

	temp.push_back(*(map[startY][startX]));

	while (!temp.empty() || temp.size() > 0)
	{	
		direction.clear();
		if (startX > 0)
		{
			if (map[startY][startX]->getWest() == NULL)
				direction.push_back('w');
		}
		if (startX < roomSize -1)
		{
			if (map[startY][startX]->getEast() == NULL)
				direction.push_back('e');
		}
		if (startY > 0)
		{
			if (map[startY][startX]->getNorth() == NULL)
				direction.push_back('n');
		}
		if (startY < roomSize - 1)
		{
			if (map[startY][startX]->getSouth() == NULL)
				direction.push_back('s');
		}
		
		if (direction.size() > 1)
		{
			//get a random direction and set the wall on that direction to door
			int i = rand() % direction.size();
			char d = direction[direction.size()-i-1];
			
			switch (d)
			{
			case 'w':

				map[startY][startX]->setWest(map[startY][startX - 1]);
				map[startY][startX - 1]->setEast(map[startY][startX]);
				--startX;
				break;
			case 'e':
				map[startY][startX]->setEast(map[startY][startX + 1]);
				map[startY][startX + 1]->setWest(map[startY][startX]);
				++startX;
				break;
			case 'n':
				map[startY][startX]->setNorth(map[startY - 1][startX]);
				map[startY - 1][startX]->setSouth(map[startY][startX]);
				--startY;
				break;
			case 's':
				map[startY][startX]->setSouth(map[startY + 1][startX]);
				map[startY + 1][startX]->setNorth(map[startY][startX]);
				++startY;
				break;
			}
			//push the neighber (new current) to temp vector
			temp.push_back(*(map[startY][startX]));
		}
		else
		{
			//remove the first item
			temp.erase(temp.begin());

			//if temp not empty after remove, get the first item in temp and set as new start point
			if (temp.size() > 0 || !temp.empty())
			{
				startY = temp[0].getRow();
				startX = temp[0].getColumn();
			}
		}
	}//finish first turn door setting

	
}



void Game::printMap()
{
	string wall = "+";
	for (int w = 0; w < map.size(); w++)
	{
		wall += "-+";
	}
	cout << wall << endl;
	string row1, row2;
	for (int r = 0; r < map.size(); r++)
	{
		//print ceil
		if (r > 0)
		{
			row2 = "+";
			for (int c = 0; c < map[r].size(); c++)
			{

				row2 += map[r][c]->getNorth() == NULL ? "-" : " ";
				/*if ((map[r][c]->getEast() == NULL && map[r][c + 1]->getWest() == NULL) || (map[r][c]->getEast() == map[r][c + 1] && map[r][c + 1]->getWest() == map[r][c]))
				a = 1;*/
				row2 += "+";
			}
			cout << row2 << endl;
		}

		 row1 = "|";
		 //print room wall
		for (int c = 0; c < map[r].size(); c++)
		{
			if (map[r][c]->getVisited() == false)
				row1 += (player->getPositionY() == r && player->getPositionX() == c) ? "P" : ".";
			else
				row1 += " ";
			if (c < map[r].size()-1)
				row1 += map[r][c]->getEast() == NULL ? "|" : " ";
				/*if ((map[r][c]->getEast() == NULL && map[r][c + 1]->getWest() == NULL) || (map[r][c]->getEast() == map[r][c + 1] && map[r][c + 1]->getWest() == map[r][c]))
					a = 1;*/
		}
		row1 += "|";
		cout << row1 << endl;
		
	}
	cout << wall << endl;
	//cout << player->getPositionX() << ", " << player->getPositionY()<<endl;
	
}

void Game::createFlogMap()
{
	flogMap.clear();
	string wall = "+";
	string row1, row2;
	for (int w = 0; w < map.size(); w++)
	{
		wall += "-+";
	}
	flogMap.push_back(wall);
	for (int j = 0; j < map.size(); j++)
	{
		//print ceil
		if (j > 0)
		{
			row2 = "+";
			for (int c = 0; c < map[j].size()-1; c++)
			{

				row2 += "**";
			}
			row2 += "*+";
			flogMap.push_back(row2);
		}
		row1 = "|";
		for (int i = 0; i < map.size()-1; i++)
		{
			row1 += "**";
		}
		row1 += "*|";
		flogMap.push_back(row1);
	}
	flogMap.push_back(wall);
	//cout << player->getPositionX() << ", " << player->getPositionY() << endl;

}

void Game::printFlogMap()
{
	int x = player->getPositionX();
	int y = player->getPositionY();
	Room* room = map[y][x];
	string replacetxt;
	flogMap[y * 2 + 1].replace(x*2+1,1,"P");
	if (x > 0)
	{
		replacetxt = room->getWest() == NULL ? " " : "|";
		flogMap[y * 2 + 1].replace(x * 2, 1, replacetxt);
	}
		
	if (x < map.size() - 1)
	{
		replacetxt = room->getEast() == NULL ? " " : "|";
		flogMap[y * 2 + 1].replace(x * 2 + 2, 1, replacetxt);
	}
		
	if (y > 0)
	{
		replacetxt = room->getNorth() == NULL ? " " : "-";
		flogMap[y * 2].replace(x * 2 + 1, 1, replacetxt);
		flogMap[y * 2].replace(x * 2, 1, "+");
		flogMap[y * 2].replace(x * 2 + 2, 1, "+");
	}

		
	if (y < map.size() - 1)
	{
		replacetxt = room->getSouth() == NULL ? " " : "-";
		flogMap[y * 2 + 2].replace(x * 2 + 1, 1, replacetxt);
		flogMap[y * 2 + 2].replace(x * 2, 1, "+");
		flogMap[y * 2 + 2].replace(x * 2 + 2, 1, "+");
	}
		
	for (int i = 0; i < flogMap.size(); i++)
	{
		cout << flogMap[i] << endl;
	}
}
void Game::createPlayer(int roomSize)
{
	int x = rand() % roomSize;
	int y = rand() % roomSize;
	player = new Player("abcd", new Vocation("Thief", 100, 50, 20));
	player->setPositionX(x);
	player->setPositionY(y);

}

void Game::playerMove(char dir)
{
	Room* current = map[player->getPositionY()][player->getPositionX()];
	//cout << player->getPositionX() << ", " << player->getPositionY() << endl;
	switch (dir)
	{
	case 'w':
		if (player->getPositionY() > 0 && current->getNorth() != NULL)
			player->setPositionY(player->getPositionY()-1);
		break;
	case 'a':
		if (player->getPositionX() > 0 && current->getWest() != NULL)
			player->setPositionX(player->getPositionX() - 1);
		break;
	case 's':
		if (player->getPositionY() < map.size() - 1 && current->getSouth() != NULL)
			player->setPositionY(player->getPositionY() + 1);
			
		break;
	case 'd':
		if (player->getPositionX() < map.size() - 1 && current->getEast() != NULL)
			player->setPositionX(player->getPositionX() + 1);
		break;
		
	default:
		cout << "wrong key" << endl;
		break;
	}
	//createFlogMap();
	//printFlogMap();
	printMap();
}

void Game::setCheatMode()
{
	cheatMode = !cheatMode;
}
bool Game::getCheatMode()
{
	return cheatMode;
}