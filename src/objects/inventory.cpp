#include "../../include/objects/inventory.hpp"

Inventory::Inventory() {
	this->inventory = List<Item>();
	this->inventoryWin = newwin(10, 13, (getmaxy(stdscr) / 2) - 10, (getmaxx(stdscr) / 2) - (70));
	box(inventoryWin, 0, 0);
	wrefresh(inventoryWin);
}

void Inventory::addToInventory(Item item) {
	this->inventory.headInsert(item);
}

void Inventory::removeFromInventory(int& tracker) {
	this->inventory.removeElement(tracker);
}

//ritorna una lista di interi rappresentanti gli ID degli item nell'inventario
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

void Inventory::printItems() {
	Node<Item> *tmp = new Node<Item>;
	tmp = inventory.getHead();
	int i = 0;

	while(tmp != NULL) {
		mvwprintw(inventoryWin, i / (inventoryWin->_maxx - 1) + 2, i % (inventoryWin->_maxx - 1) + 1, tmp->getData()->getProperties().icon);
		i++;
		tmp = tmp->getNext();
	}
	wrefresh(inventoryWin);
}

void Inventory::printTitle() {
	mvwprintw(inventoryWin, 1, 1, "INVENTARIO:");
	wrefresh(inventoryWin);
}
