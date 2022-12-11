#ifndef ITEMS
#define ITEMS

#include "../assets/hch.h"
#include "entity.hpp"
#include "../assets/itemLists.hpp"




/**
 * @brief Class that represents an item in the game (entity)
*/
class Item : public Entity
{
private:
	itemProperties properties;

public:
	//default constructor (necessary to initialize Lists of Items)
	Item();
	// Used to create a new Item within lists
	Item(itemProperties properties, Position position, WINDOW* win);
	// returns the properties of an initialized Item
	itemProperties getProperties();
};

// Finds the itemProperties of an item with a specific ID from the itemList
itemProperties findItem(int ID);
itemProperties findItem(const char* name);

#endif