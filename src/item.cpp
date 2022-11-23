#include "../lib/listUtils.hpp"
#include "../lib/item.hpp"
#include "../assets/itemLists.hpp"

// Da spostare da qualche altra parte
itemProperties findItem(itemProperties items[], int ID) {
	for (int i = 0; i < sizeof(items) / sizeof(items[0]); i++) {
		if (items[i].ID == ID) {
			return items[i];
		}
	}
}

Item::Item() : Entity(){
	this->properties = findItem(_Debug, 11); // returns the itemProperties of the item with ID 11
}

Item::Item(itemProperties properties, Position position, WINDOW* win) : Entity(properties.icon, position, win) {
	this->properties = properties;
}

itemProperties Item::getProperties()
{
	return this->properties;
}