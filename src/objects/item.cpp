#include "../../include/objects/item.hpp"
#include "../../include/assets/item_properties_array.hpp"
#include "../../include/util/listUtils.hpp"
#include "../../include/util/engine.hpp"


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
		if (strcmp(itemList[i].icon, icon) == 0) {
			return itemList[i];
		}
	}
	return findItem("+");
}

Item::Item() : Entity(){
	this->properties = findItem(11); // returns the itemProperties of the default debug item
}

Item::Item(itemProperties properties, Position position, WINDOW* win) : Entity(properties.icon, position, win) {
	this->properties = properties;
}

void Item::spawn(){
	if(this->properties.type == ARTIFACT){
		wattron(current_room_win, COLOR_PAIR(ARTIFACT_PAIR));
		mvwprintw(current_room_win, current_position.y, current_position.x, icon);
		wattroff(current_room_win, COLOR_PAIR(ARTIFACT_PAIR));
	}
	else if(this->properties.type == BUFF){
		wattron(current_room_win, COLOR_PAIR(BUFF_PAIR));
		mvwprintw(current_room_win, current_position.y, current_position.x, icon);
		wattroff(current_room_win, COLOR_PAIR(BUFF_PAIR));
	}
	else if(this->properties.type == DEBUFF){
		wattron(current_room_win, COLOR_PAIR(DEBUFF_PAIR));
		mvwprintw(current_room_win, current_position.y, current_position.x, icon);
		wattroff(current_room_win, COLOR_PAIR(DEBUFF_PAIR));
	}
	else if(this->properties.type == WEAPON){
		wattron(current_room_win, COLOR_PAIR(WEAPON_PAIR));
		mvwprintw(current_room_win, current_position.y, current_position.x, icon);
		wattroff(current_room_win, COLOR_PAIR(WEAPON_PAIR));
	}
}

void Item::spawn(Position position){
	current_position = position;
	spawn();
}

itemProperties Item::getProperties()
{
	return this->properties;
}