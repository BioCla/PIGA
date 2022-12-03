#ifndef ITEMS
#define ITEMS

#include "../assets/hch.h"
#include "entity.hpp"

enum ItemType {
	BUFF, // Colore verde
	DEBUFF, // colore rosso
	ARTIFACT, // colore giallo
	WEAPON, // colore blu
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

/**
 * List of all the items in the game
 * 
 * The ID of each item is the index of the item in the list
 * used to identify the item within a list and match it with a specific effect
 * which can be implemented in various ways outside of this file as well:
 * 
 * perhaps: on pickup, the item is added to the player's inventory
 * and the effect is applied to the player
 * 
 * @example if (item->getProperties().ID == 0) { character->addHealth(10); }
 * @example if (item->getProperties().ID == 1) { // do something }
 */

#endif