#ifndef ITEMS
#define ITEMS

#include "../assets/hch.h"
#include "entity.hpp"

class item
{
private:
	int id;
	const char *name;
	int posx, posy;

public:
	item(int id, const char *name);
	void setID(int id);
	void setName(const char *name);
	int getID();
	const char *getName();
	void setPos(int x, int y);
};

void initItemDict(item itemList[]);

#endif