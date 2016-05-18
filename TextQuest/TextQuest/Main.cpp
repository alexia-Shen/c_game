﻿// Main.cpp
// CPlusPlusQuest (A2 Sample Solution)
// Created by Peter Hoghton on 22/04/2016
// Tim 3/5/16 - some cleanup and refactoring with extra things we covered in lectures (factory, singleton, friend, operator<< override, etc)

#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <vector>

#include "Main.h"
#include "Character.h"
#include "Player.h"
#include "Enemy.h"
#include "Vocation.h"
#include "Event.h"
#include "EnemyFactory.h"；
//------------------------------------------------
// Global variables like these would ideally be data members within a separate 'Game' class
//------------------------------------------------
Player* player;
vector<Vocation*> vocations;
vector<Event*> events;
//------------------------------------------------

void main() {

	//Initializes random seed
	srand(static_cast<unsigned>(time(NULL)));

	startGame();

	system("pause");
}

//Game set up
void startGame() {

	fstream myfile;
	string vocation, description;
	int health, strength, magic, healthModifier;
	char comma, continueChoice;
	
	//Iterates through the vocations text file and stores each vocation in a vector as an object
	myfile.open("vocations.txt");

	string line;
	while(getline(myfile, line)) {
		stringstream ss(line);
		getline(ss, vocation, ',');
		ss >> health >> comma >> strength >> comma >> magic;
		vocations.push_back(new Vocation(vocation, health, strength, magic));
	}
	myfile.close();

	//Iterates through the events text file and stores each event in a vector as an object
	myfile.open("events.txt");
	while (getline(myfile, line)) {
		stringstream ss(line);
		getline(ss, description, ',');
		ss >> healthModifier;
		events.push_back(new Event(description, healthModifier));
	}
	myfile.close();

	cout << "Welcome to CPlusPlusQuest!" << endl;

	continueChoice = 'x';

	//Checks if there are any existing saves present before prompting to load one or create a new character
	if (countLinesInFile("saves.txt") > 0) {

		cout << "Existing save(s) found!" << endl;

		while (continueChoice != 'y' && continueChoice != 'n') {
			cout << "Would you like to load an existing character? (y/n) ";
			cin >> continueChoice;
		}

		//Ignores any extra input (ensures extra input is not accidently read in by future 'cin' or 'getline' commands
		cin.ignore();

		if (continueChoice == 'y') {
			loadGame();
		}
		else {
			createCharacter();
		}
	}
	//No saves present, create a new character
	else{
		cout << "No existing save(s) found." << endl;
		createCharacter();
	}

	cout << player->getName() << " the " << *player->getVocation() << " is ready to begin their quest!" << endl;

	continueChoice = 'x';

	while (continueChoice != 'y' && continueChoice != 'n') {
		cout << "Would you like to begin? (y/n) ";
		cin >> continueChoice;
	}

	//Ignores any extra input (ensures extra input is not accidently read in by future 'cin' or 'getline' commands
	cin.ignore();

	//Starts main game loop
	if (continueChoice == 'y') {
		gameLoop();
	}

	cout << "Thanks for playing!" << endl;

	// cleanup
	for (Vocation* v : vocations) delete v;
	for (Event* e : events) delete e;
	delete player;
}

//The main game loop
void gameLoop() {

	char continueChoice = 'x';

	do {
		//25% chance of a fight occuring each round
		int fightChance = rand() % 4;

		//Start a fight
		if (fightChance == 0) {
			fight();
		}
		//Otherwise apply random event
		else {
			//Chooses a random number between 0 and the number of events
			int randEvent = rand() % events.size();

			//Outputs random event information and modifies character's health accordingly
			cout << events[randEvent]->getDescription() << endl;
			player->setHealth(player->getHealth() + events[randEvent]->getHealthModifier());
		}

		//Checks if player is still alive
		if (player->getHealth() > 0) {

			cout << player->getName() << " has " << player->getHealth() << " health remaining." << endl;

			continueChoice = 'x';

			while (continueChoice != 'y' && continueChoice != 'n') {
				cout << "Would you like to continue? (y/n) ";
				cin >> continueChoice;
			}
		}
		//Player is dead
		else {
			player->setHealth(0);
			cout << player->getName() << " has no health remaining." << endl;
		}

	} while (player->getHealth() > 0 && continueChoice != 'n');

	continueChoice = 'x';

	//Only allow saving if player is still alive (prevents being able to load a dead character next time)
	if (player->getHealth() > 0) {
		while (continueChoice != 'y' && continueChoice != 'n') {
			cout << "Would you like to save your game? (y/n) ";
			cin >> continueChoice;
		}
	}

	if (continueChoice == 'y') {
		saveGame();
	}
}

// Fight! Fight! Fight!
// create some enemies and them together with the player into a vector of Character*
// thanks to polymorphism nothing in this function is hard coded for any subtype of Character.
void fight() {
	vector<Character*> participants;

	//Adds player to participants vector
	participants.push_back(player);

	//Adds random number of enemies (between 1 and 3) of random type with random stats to participants vector
	int numEnemies = rand() % 3 + 1;
	for (int i = 0; i < numEnemies; i++) {
		participants.push_back(EnemyFactory::getInstance()->makeEnemy());
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

	//Iterates through the participants vector and deletes all participants (but not the player!)
	for (Character* p : participants) {
		if (p != player) {
			delete p;
		}
	}
}

//Creates a new character
void createCharacter() {

	string nameInput;
	unsigned inputChoice = 0;

	cout << "Creating a new character!" << endl;

	while (nameInput == "") {
		cout << "Please enter a name for your character: ";
		getline(cin, nameInput);
	}

	while (inputChoice < 1 || inputChoice > vocations.size()) {

		cout << "Please select a vocation by entering a number below: " << endl;

		//Iterates through the vocations vector and outputs each vocation
		inputChoice = 1;
		for (Vocation* v : vocations) {
			cout << inputChoice++ << ": " << *v << endl;
		}

		cin >> inputChoice;
	}

	//Creates a new character object based on nameInput and inputChoice (see above)
	player = new Player(nameInput, vocations[inputChoice - 1]);

	saveGame();
}

//Reads in existing character stats from file
void loadGame() {

	fstream myfile;
	string name, vocationType;
	int health, strength, magic;
	int inputChoice = 0;
	char comma;

	while (inputChoice < 1 || inputChoice > countLinesInFile("saves.txt")) {

		cout << "Please select a character by entering a number below: " << endl;

		//Iterates through the saves text file and outputs each character
		myfile.open("saves.txt");
		int lineNumber = 0;
		string line;
		while (getline(myfile, line)) {
			stringstream ss(line);
			getline(ss, name, ',');
			getline(ss, vocationType, ',');
			cout << lineNumber + 1 << ": " << name << " the " << vocationType << endl;
			lineNumber++;
		}
		myfile.close();

		cin >> inputChoice;
	}

	//Goes to specific character (line) in text file based on inputChoice
	myfile.open("saves.txt");
	for (int i = 0; i < inputChoice - 1; i++) {
		getline(myfile, name);
	}

	//Reads in stats for character based on inputChoice (see above)
	getline(myfile, name, ',');
	getline(myfile, vocationType, ',');
	myfile >> health >> comma >> strength >> comma >> magic;
	myfile.close();
	Vocation* vocation = NULL;
	for (Vocation* v : vocations) {
		if (v->getName() == vocationType) {
			vocation = v;
		}
	}

	//Creates a new character object using stats read in from file
	player = new Player(name, vocation);
	player->setHealth(health);
	player->setStrength(strength);
	player->setMagic(magic);

	cout << "Load successful!" << endl;

}

//Writes character stats to file
void saveGame() {
	
	fstream myfile;

	//Opens file in 'append' mode (meaning it will always write to the end of the file)
	myfile.open("saves.txt", ios::app);
	myfile << player->getName() << "," << (*player->getVocation()) << "," << player->getHealth() << "," << player->getStrength() << "," << player->getMagic() << "\n";
	myfile.close();

	cout << "Save successful!" << endl;
}

//Utility function that returns the number of lines in a given file
int countLinesInFile(string file) {

	fstream myfile;
	int numLines = 0;
	string line;

	myfile.open(file);
	while (getline(myfile, line)) {
		numLines++;
	}
	myfile.close();

	return numLines;
}