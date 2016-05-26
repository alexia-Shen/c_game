// Event.h

#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>

using namespace std;
class Item
{
private:
	string name;
	string description;
	char type;
	int modifier;

public:

	Item();
	Item(string n, string d, char t, int m);
	int modify(int base);

	void setName(string n);
	void setDescription(string d);
	void setType(char t);
	void setmodifier(int m);

	string getName();
	string getDescription();
	char getType();
	int getRank();
	int getModifier();
};
#endif