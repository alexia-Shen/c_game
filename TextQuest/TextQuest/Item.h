// Event.h

#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>

using namespace std;
class Item
{
protected: 

	string name;
	string description;
	int modifier;

public:

	Item();
	Item(string n, string d, int m);
	int modify(int base);

	void setName(string n);
	void setDescription(string d);
	void setRank(int r);
	void setmodifier(int m);
	
	string getName();
	string getDescription();
	int getRank();
	int getModifier();
};
#endif