#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <vector>
#include<conio.h>
#include<windows.h>
#include "Game.h"
#include "Room.h"
#include "Vocation.h"
#include "Player.h"


vector<Vocation* > vocations;
vector<Event* > events;
Game* gm;



int countLinesInFile(string file);
void createCharacter();
void loadGame();
void startGame();

void loadVocations();
void loadEvents();
void fight(Room* room);

void gameLoop();
void mapLoop(bool &keepMap);
void gameMenu();
void startGame();
void displayPlayerInfo();

