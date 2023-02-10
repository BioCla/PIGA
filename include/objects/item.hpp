#ifndef ITEMS
#define ITEMS

#include "../assets/hch.h"
#include "../assets/entity.hpp"
#include "../assets/itemLists.hpp"

class Item : public Entity
{
private:
	itemProperties properties;

public:
	Item();
	Item(itemProperties properties, Position position, WINDOW* win);
	itemProperties getProperties();
	void spawn();
	void spawn(Position position);
};

// associa proprieta' ad un item di un certo ID
itemProperties findItem(int ID);
itemProperties findItem(const char* icon);

#endif