#ifndef ITEMS
#define ITEMS

#include "../assets/hch.h"
#include "entity.hpp"

enum ItemType {
	BUFF, // Colore verde
	DEBUFF, // colore rosso
	ARTIFACT, // colore giallo
	WEAPON, // colore blu
	DEBUG, // nessun colore
};

struct itemProperties {
	const char* name;
	const char* description;
	const char* icon;
	int ID;
	ItemType type;
};

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