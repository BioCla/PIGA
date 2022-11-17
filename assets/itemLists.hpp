
#ifndef ITEMS_LIST
#define ITEMS_LIST
#include "../lib/item.hpp"

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