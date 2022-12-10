#include "../lib/listUtils.hpp"
#include "../lib/item.hpp"
#include "../assets/itemLists.hpp"

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