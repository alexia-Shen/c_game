

#include <iostream>
#include <string>
#include "Item.h"
#include "Player.h"

using namespace std;

Item::Item()
{
}
Item::Item(string n, string d, int m)
{
	name = n;
	description = d;
	modifier = m;
}


void Item::setName(string n)
{
	name = n;
}
void Item::setDescription(string d)
{
	description = d;
}

void Item::setmodifier(int m)
{
	modifier = m;
}

string Item::getName()
{
	return name;
}

string Item::getDescription()
{
	return description;
}

int Item::getModifier()
{
	return modifier;
}
int Item::modify(int base)
{
	return base + modifier;
}