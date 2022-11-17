#ifndef ITEMS
#define ITEMS

#include "../assets/hch.h"
#include "entity.hpp"

enum ItemType {
	BUFF,
	DEBUFF,
	ARTIFACT,
	WEAPON,
};

struct Properties {
	const char* name;
	const char* description;
	const char* icon;
	int ID;
	ItemType type;
};

class Item : public Entity
{
private:
	Properties properties;

public:
	// Used to create a new Item within lists
	Item(Properties properties, Position position, WINDOW* win);
	// returns the properties of an initialized Item
	Properties getProperties();
};

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

// Properties of the effects you can find in the game
Properties effects[] = {
	{"Health UP!", "Increases your max health by 1", "H", 0, BUFF},
	{"Damage UP!", "Increases your damage by 1", "D", 1, BUFF},
	{"Speed UP!", "Increases your speed by 1", "S", 2, BUFF},
	{"Health DOWN!", "Decreases your max health by 1", "h", 3, DEBUFF},
	{"Damage DOWN!", "Decreases your damage by 1", "d", 4, DEBUFF},
	{"Speed DOWN!", "Decreases your speed by 1", "s", 5, DEBUFF},
	{"Heart", "Add one Health point if you were missing some", "♥", 9, BUFF},
};

// Properties of the artifacts you can find in the game
Properties artifacts[] = {
	{"Key", "Opens doors", "K", 6, ARTIFACT},
	{"LAZER!!!!!", "IMA LAZERBEAMMMMMM", "L", 7, WEAPON},
	{"BOMB!", "Explodes", "B", 8, WEAPON},
};

#endif