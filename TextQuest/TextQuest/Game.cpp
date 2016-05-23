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
				row1 += (player->getPositionY() == r && player->getPositionX() == c) ? "P" : " ";
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

//locate player at the beginning of game
void Game::locatePlayer(Player* p, int positionX, int positionY)
{
	int x, y;
	player = p;
	if (positionX == -1 || positionY == -1)
	{
		x = rand() % map.size();
		y = rand() % map.size();
	}
	else
	{
		x = positionX;
		y = positionY;
	}
	player->setPositionX(x);
	player->setPositionY(y);

}

//player move around the map
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
	if (cheatMode != true)
	{
		createFlogMap();
		printFlogMap();
	}
	else
		printMap();
}

void Game::setPlayer(Player* p)
{
	player = p;
}
Player* Game::getPlayer()
{
	return player;
}
void Game::setCheatMode()
{
	cheatMode = !cheatMode;
}
bool Game::getCheatMode()
{
	return cheatMode;
}

// Fight! Fight! Fight!
// load room enemies and them together with the player into a vector of Character*
// thanks to polymorphism nothing in this function is hard coded for any subtype of Character.

bool Game::checkRoom()
{
	Room* current = map[player->getPositionY()][player->getPositionX()];
	cout << player->getPositionX() << "," << player->getPositionY() << endl;
	return ((current->getEnemies().size() != 0 || current->getEvents().size() != 0) && !current->getVisited());
}


void Game::fight()
{
	Room* current = map[player->getPositionY()][player->getPositionX()];

	vector<Enemy* > ems = current->getEnemies();
	vector<Character*> participants;

	if (current->getVisited() == true || ems.size()<=0)
		return;
	//Adds player to participants vector
	participants.push_back(player);
	system("CLS");
	cout << "----------Start fighting!-------------" << endl;
	
	cout << "There are " << ems.size() << " enemies in the queue";
	//Add enemies in the room to parcipants
	for (int i = 0; i < ems.size(); i++) {
		participants.push_back(ems[i]);
	}

	cout << "A fight has started!" << endl;

	//Fight continues until player is defeated or there are no enemies left
	vector<Character*> stillAlive = participants;
	while (player->getHealth() > 0 && stillAlive.size() > 1) {

		//Iterates through the participants vector and calls each character's attack function
		for (Character* attacker : stillAlive) {
			//Ensures that any defeated participants do not get to attack
			if (attacker->getHealth() > 0) {
				cout << "It is " << attacker->getName() << "'s turn to attack!" << endl;
				system("pause");
				attacker->attack(stillAlive);
			}
		}

		// remove dead participants
		// (by extracting the ones that are alive into a new vector and then copying it back to the original)
		vector<Character*> tmp;
		for (Character* c : stillAlive) {
			if (c->getHealth() > 0) {
				tmp.push_back(c);
			}
		}
		stillAlive = tmp;
	}
	cout << "The fight is over!" << endl;
	player->setHealth(100);

	//Iterates through the participants vector and deletes all participants (but not the player!)
	for (Character* c : participants)
	{
		if (c != player)
			delete c;
	}
}

void Game::executeEvents()
{
	Room* current = map[player->getPositionY()][player->getPositionX()];
	vector<Event* > evets = current->getEvents();
	if (current->getVisited() == true)
		return;
	if (evets.size() <= 0)
	{
		current->setVisited(true);
		cout << "No events in this room!" << endl;
		return;
	}
	for (Event* e : evets)
	{
		cout << e->getDescription() << endl;
		player->setHealth(player->getHealth() + e->getHealthModifier());
	}

	cout << "End of events" << endl;
	for (Event* e : evets)
		delete e;
	current->setVisited(true);
}