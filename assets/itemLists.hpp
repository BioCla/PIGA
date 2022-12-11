
#ifndef ITEMS_LIST
#define ITEMS_LIST


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


#endif