#include "../lib/listUtils.hpp"
#include "../lib/item.hpp"

Item::Item() : Entity(){
	this->properties = { "default", "default", "default", 0, BUFF };
}

Item::Item(itemProperties properties, Position position, WINDOW* win) : Entity(properties.icon, position, win) {
	this->properties = properties;
}

itemProperties Item::getProperties()
{
	return this->properties;
}