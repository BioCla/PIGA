#include "../lib/listUtils.hpp"
#include "../lib/item.hpp"
//#include "../assets/itemLists.hpp"

itemProperties itemList[] = { 
// Debug items
	{"Misc", "Misc", "Misc", 10, DEBUG},
	{ "default", "default", "default", 11, DEBUG},

// itemProperties of the effects you can find in the game
	{"Health UP!", "Increases your max health by 1", "H", 0, BUFF},
	{"Damage UP!", "Increases your damage by 1", "D", 1, BUFF},
	{"Speed UP!", "Increases your projectile speed by 10", "S", 2, BUFF},
	{"Health DOWN!", "Decreases your max health by 1", "h", 3, DEBUFF},
	{"Damage DOWN!", "Decreases your damage by 1", "d", 4, DEBUFF},
	{"Speed DOWN!", "Decreases your projectile speed by 10", "s", 5, DEBUFF},
	{"Heart", "Add one Health point if you were missing some", "♥", 9, BUFF},

// itemProperties of the artifacts you can find in the game
	{"Key", "Opens doors", "K", 6, ARTIFACT},
	{"LAZER!!!!!", "IMA LAZERBEAMMMMMM", "L", 7, WEAPON},
	{"BOMB!", "Explodes", "B", 8, WEAPON},
};

itemProperties findItem(int ID) {
	int length = sizeof(itemList) / sizeof(itemProperties);
	for (int i = 0; i < length; i++) {
		if (itemList[i].ID == ID) {
			return itemList[i];
		}
	}
	return findItem(11);
}

itemProperties findItem(const char* icon) {
	int length = sizeof(itemList) / sizeof(itemProperties);
	for (int i = 0; i < length; i++) {
		if (itemList[i].icon == icon) {
			return itemList[i];
		}
	}
	return findItem("default");
}

Item::Item() : Entity(){
	this->properties = findItem(11); // returns the itemProperties of the default debug item
}

Item::Item(itemProperties properties, Position position, WINDOW* win) : Entity(properties.icon, position, win) {
	this->properties = properties;
}

itemProperties Item::getProperties()
{
	return this->properties;
}