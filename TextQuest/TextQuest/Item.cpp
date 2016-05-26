

#include <iostream>
#include <string>
#include "Item.h"

using namespace std;

Item::Item()
{
}

Item::Item(string n, string d, char t, int m)
{
	name = n;
	description = d;
	type = t;
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
void Item::setType(char t)
{
	type = t;
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
char Item::getType()
{
	return type;
}
int Item::modify(int base)
{
	return base + modifier;
}