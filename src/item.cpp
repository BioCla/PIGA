#include "../lib/listUtils.hpp"
#include "../lib/item.hpp"

Item::Item(Properties properties, Position position, WINDOW* win) : Entity(properties.icon, position, win) {
	this->properties = properties;
}

Properties Item::getProperties()
{
	return this->properties;
}