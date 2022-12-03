#include "../lib/inventory.hpp"

Inventory::Inventory() {
	this->inventory = List<Item>();
}

void Inventory::addToInventory(Item item) {
	this->inventory.headInsert(item);
}

void Inventory::removeFromInventory(int& tracker) {
	this->inventory.removeElement(tracker);
}

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

void Inventory::printInventory(WINDOW* win) {
	int* inventory = this->getInventory();
	int length = this->inventory.listLength();

	for (int i = 0; i < length; i++) {
		wprintw(win, "%s", findItem(inventory[i]).name);
	}
}