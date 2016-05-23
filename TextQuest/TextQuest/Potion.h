

#ifndef POTION_H
#define POTION_H

#include "Item.h"
#include <iostream>
#include <string>

class Potion: public Item
{
	Potion();
	Potion(string n,string d,int m);
};
#endif