#include "../../include/objects/inventory.hpp"

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
List<int> Inventory::getInventory() {
	List<Item> tmp = this->inventory;
	Node<Item>* tmpHead = tmp.getHead();

	int length = tmp.listLength();
	List<int> itemTracker = List<int>();
	for (int i = 0; i < length; i++) {
		itemTracker.headInsert(tmpHead->getData()->getProperties().ID);
		tmpHead = tmpHead->getNext();
	}
	return itemTracker;
}