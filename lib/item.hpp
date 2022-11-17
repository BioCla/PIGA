#ifndef ITEMS
#define ITEMS

#include "../assets/hch.h"
#include "entity.hpp"

class Item : public Entity
{
private:
	const char *name;

public:
	Item(char icon, const char *name);
	void setName(const char *name);
	const char *getName();
};

void initItemDict(Item itemList[]);

#endif