
#include "Main.h"
using namespace std;
void main()
{
	gm = Game::createNewGame();
	startGame();
	system("pause");
}


//Game set up
void startGame() {

	char continueChoice;
	loadVocations();
	gm->loadEvents();


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

	cout << gm->getPlayer()->getName() << " the " << gm->getPlayer()->getVocation()->getName() << " is ready to begin their quest!" << endl;

	continueChoice = 'x';

	while (continueChoice != 'y' && continueChoice != 'n') {
		cout << "Would you like to begin? (y/n) ";
		cin >> continueChoice;
	}

	//Ignores any extra input (ensures extra input is not accidently read in by future 'cin' or 'getline' commands
	cin.ignore();

	//Starts main game loop
	if (continueChoice == 'y') {
		system("CLS");
		gameMenu();
	}

	gm->saveGame();
	gm->saveMap();
	gm->saveInventory();
	cout << "Thanks for playing!" << endl;

	// cleanup
	for (Vocation* v : vocations) delete v;
	for (Event* e : events) delete e;
	delete gm;
}

//create a new character
void createCharacter()
{
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

	int x = rand() % 10;
	int y = rand() % 10;
	Player* player = new Player(nameInput, vocations[inputChoice - 1]);
	gm->fillMap(10);
	gm->createDoors(10);

	player->setPositionX(x);
	player->setPositionY(y);
	gm->setPlayer(player);

	gm->saveGame();
	gm->saveMap();
}


//Reads in existing character stats from file
void loadGame() {

	fstream myfile;
	string name, vocationType;
	string mapOwner;
	int health, strength, magic;
	int positionY, positionX;
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
	myfile >> health >> comma >> strength >> comma >> magic >> comma;
	getline(myfile, mapOwner, ',');
	myfile >> positionX >> comma >> positionY;
	 
	myfile.close();
	Vocation* vocation = NULL;
	for (Vocation* v : vocations) {
		if (v->getName() == vocationType) {
			vocation = v;
		}
	}
	//Creates a new character object using stats read in from file
	Player* player = new Player(name, vocation);
	player->setHealth(health);
	player->setStrength(strength);
	player->setMagic(magic);
	player->setPositionX(positionX);
	player->setPositionY(positionY);
	gm->setPlayer(player);
	gm->loadInventory();//load inventory from save

	//cout << gm->getPlayer()->getItems().size() << " size" << endl;
	//start load map
	if (mapOwner.compare("null") != 0 && gm->loadMap(mapOwner))
	{
		cout << "Load successful!" << endl;
	}
	else
	{
		cout << "Map record not found, A new map generated for you!" << endl;

		gm->fillMap(10);
		gm->createDoors(10);
	}
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

void loadVocations()
{
	fstream myfile;
	string vocation;
	int health, strength, magic, healthModifier;
	char comma;
	//Iterates through the vocations text file and stores each vocation in a vector as an object
	myfile.open("vocations.txt");

	string line;
	while (getline(myfile, line)) {
		stringstream ss(line);
		getline(ss, vocation, ',');
		ss >> health >> comma >> strength >> comma >> magic;
		vocations.push_back(new Vocation(vocation, health, strength, magic));
	}
	myfile.close();

}

void gameMenu()
{
	bool countinue = true;
	char menuInput;
	while (countinue == true)
	{
		system("CLS");
		if (gm->getPlayer()->getHealth() > 0)
		{
			cout << "Choose your option: " << endl;
			cout << "1. change cheat mode (Currently: " << gm->getCheatMode() << ")" << endl;
			cout << "2. enter map" << endl;
			cout << "3. check your statement" << endl;
			cout << "4. quit game" << endl;
			cin >> menuInput;
			switch (menuInput)
			{
			case '1':
				gm->setCheatMode();
				cout << "Cheat mode changed!" << endl;
				break;
			case '2':
				gameLoop();
				break;
			case '3':
				displayPlayerInfo();
				break;
			case '4':
				countinue = false;
				break;
			default:
				break;
			}
		}
		else
		{
			cout << "Game over!" << endl;
			countinue = false;
		}
	}
}

void gameLoop()
{
	bool keep = true;
	while (keep)
	{
		mapLoop(keep);
		if (keep)
		{
			gm->fight();
			gm->executeEvents();
		}
			
		if (gm->getPlayer()->getHealth() <= 0)
		{
			keep = false;
			cout << "You are dead!" << endl;
		}
		system("pause");
	}
}

void mapLoop(bool &keepMap)
{
	char input;
	bool keep = true;
	bool meetEnemy = false;
	system("CLS");
	cout << "Use keyboard to move player!" << endl;
	cout << "Up: w; Left: a; Down: s; Right: d;" << endl;
	cout << "Quit game: space" << endl;
	if (gm->getCheatMode())
		gm->printMap();
	else
	{
		gm->createFlogMap();
		gm->printFlogMap();
	}
	
	while (keep && !meetEnemy)
	{
		if (_kbhit())
		{
			Sleep(100);
			system("CLS");
			input = _getch();
			cout << "Use keyboard to move player!" << endl;
			cout << "Up: w; Left: a; Down: s; Right: d;" << endl;
			cout << "Quit game: space" << endl;
			gm->playerMove(input);
			if (input == 32)
			{
				keep = false;
				keepMap = false;
				cout << "end" << endl;
				break;
			}
			if (gm->checkRoom())
			{
				Sleep(100);
				meetEnemy = true;
				break;
			}
		}
	}
}

void displayPlayerInfo()
{
	Player* temp = gm->getPlayer();
	cout << "Player name: " << temp->getName() << endl;
	cout << "Health: " << temp->getHealth() << ", Strength: " << temp->getStrength() << ", Magic: " << temp->getMagic() << endl;

	cout << "Inventory: " << endl;
	for (int i = 0; i < temp->getItems().size();i++)
	{
		cout << i + 1 << ". " << temp->getItems()[i]->getName() << ", " << temp->getItems()[i]->getDescription() << endl;
	}
	system("Pause");
}

