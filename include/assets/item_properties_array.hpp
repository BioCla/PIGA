
#ifndef ITEM_PROPERTIES_ARRAY
#define ITEM_PROPERTIES_ARRAY


#include "../../include/objects/item.hpp"

itemProperties itemList[] = { 
// Debug items
	{"Misc", "Misc", "-", 10, DEBUG},
	{ "default", "default", "+", 11, DEBUG},

// itemProperties effetti
	{"Health UP", "Increases your max health by 1", "H", 0, BUFF},
	{"Damage UP", "Increases your damage by 3", "D", 1, BUFF},
	{"Speed UP", "Increases your projectile speed by 10", "S", 2, BUFF},
	{"Health DOWN", "Decreases your max health by 1", "h", 3, DEBUFF},
	{"Damage DOWN", "Decreases your damage by 1", "d", 4, DEBUFF},
	{"Speed DOWN", "Decreases your projectile speed by 10", "s", 5, DEBUFF},
	{"Heart", "Add ten Health point if you were missing some", "V", 9, BUFF},

// itemProperties chiave
	{"Key", "Opens doors", "K", 6, ARTIFACT},

// itemProperties armi
	{"LASER", "laser", "L", 7, WEAPON},
	{"BOMB", "Explodes", "B", 8, WEAPON},
	{"BASE", "Base projectile", "P", 12, WEAPON},
};



#endif