#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <vector>
#include<conio.h>
#include<windows.h>
#include "Game.h"
#include "Room.h"

vector<vector<Room *>> map;
vector<string> flogMap;
Game* gm;

void main()
{
	cout << "hello!"<<endl;
	gm = Game::createNewGame();
	gm->fillMap(10);
	gm->createDoors(10);
	gm->createPlayer(10);
	gm->printMap();
	gm->createFlogMap();
	gm->printFlogMap();
	char input;
	bool keep = true;
	while (keep)
	{
		
		
		if(_kbhit())
		{
			Sleep(100);
			system("CLS");
			input = _getch();
			if (input == 32)
			{
				keep = false;
				cout << "end" << endl;
				break;
			}
			gm->playerMove(input);
			
		}
		
	}
	system("pause");
}
