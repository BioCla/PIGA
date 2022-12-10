
#ifndef ITEMS_LIST
#define ITEMS_LIST
#include "../lib/item.hpp"


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
	{"Misc", "Misc", "Misc", 10, WEAPON},
	{ "default", "default", "default", 11, WEAPON },

// itemProperties of the effects you can find in the game
	{"Health UP!", "Increases your max health by 1", "H", 0, BUFF},
	{"Damage UP!", "Increases your damage by 1", "D", 1, BUFF},
	{"Speed UP!", "Increases your speed by 1", "S", 2, BUFF},
	{"Health DOWN!", "Decreases your max health by 1", "h", 3, DEBUFF},
	{"Damage DOWN!", "Decreases your damage by 1", "d", 4, DEBUFF},
	{"Speed DOWN!", "Decreases your speed by 1", "s", 5, DEBUFF},
	{"Heart", "Add one Health point if you were missing some", "♥", 9, BUFF},

// itemProperties of the artifacts you can find in the game
	{"Key", "Opens doors", "K", 6, ARTIFACT},
	{"LAZER!!!!!", "IMA LAZERBEAMMMMMM", "L", 7, WEAPON},
	{"BOMB!", "Explodes", "B", 8, WEAPON},
};

#endif