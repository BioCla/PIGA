
#ifndef ITEM_PROPERTIES_ARRAY
#define ITEM_PROPERTIES_ARRAY


#include "../../include/objects/item.hpp"

/**
 * List of all the items in the game
 * 
 * The ID of each item is used to identify the item within a list and 
 * match it with a specific effect which can be implemented in various 
 * ways outside of this file as well:
 * 
 * perhaps: on pickup, the item is added to the player's inventory
 * and the effect is applied to the player
 * 
 * @example if (item->getProperties().ID == 0) { character->addHealth(10); }
 * @example if (item->getProperties().ID == 1) { // do something }
 */
itemProperties itemList[] = { 
// Debug items
	{"Misc", "Misc", "-", 10, DEBUG},
	{ "default", "default", "+", 11, DEBUG},

// itemProperties of the effects you can find in the game
	{"Health UP!", "Increases your max health by 1", "H", 0, BUFF},
	{"Damage UP!", "Increases your damage by 3", "D", 1, BUFF},
	{"Speed UP!", "Increases your projectile speed by 10", "S", 2, BUFF},
	{"Health DOWN!", "Decreases your max health by 1", "h", 3, DEBUFF},
	{"Damage DOWN!", "Decreases your damage by 1", "d", 4, DEBUFF},
	{"Speed DOWN!", "Decreases your projectile speed by 10", "s", 5, DEBUFF},
	{"Heart", "Add ten Health point if you were missing some", "V", 9, BUFF},

// itemProperties of the artifacts you can find in the game
	{"Key", "Opens doors", "K", 6, ARTIFACT},
	{"LAZER!!!!!", "IMA LAZERBEAMMMMMM", "L", 7, WEAPON},
	{"BOMB!", "Explodes", "B", 8, WEAPON},
	{"BASE", "Base projectile", "P", 12, WEAPON},
};



#endif