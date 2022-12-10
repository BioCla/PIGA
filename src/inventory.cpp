#include "../lib/inventory.hpp"

Inventory::Inventory() {
	this->inventory = List<Item>();
	this->inventoryWin = newwin(10, 11, (getmaxy(stdscr) / 2) - (50/2), (getmaxx(stdscr) / 2) - ((211/2)));
	box(inventoryWin, 0, 0);
	wrefresh(inventoryWin);
}

void Inventory::addToInventory(Item item) {
	this->inventory.headInsert(item);
}

void Inventory::removeFromInventory(int& tracker) {
	this->inventory.removeElement(tracker);
}

/**
 * Returns an array of integers representing the IDs of the items in the inventory of the player
*/
int* Inventory::getInventory() {
	List<Item> tmp = this->inventory;
	Node<Item>* tmpHead = tmp.getHead();

	int length = tmp.listLength();
	int itemTracker[length];
	for (int i = 0; i < length; i++) {
		itemTracker[i] = tmpHead->getData()->getProperties().ID;
		tmpHead = tmpHead->getNext();
	}
	return itemTracker;
}

/**
 * Prints the inventory to the screen in the inventory window
*/
void Inventory::printInventory() {
	int* inventory = this->getInventory();
	int length = this->inventory.listLength();

	for (int i = 0; i < length; i++) {
		wprintw(inventoryWin, "%s", findItem(inventory[i]).name);
	}
}