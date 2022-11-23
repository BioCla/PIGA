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

List<Item> Inventory::getInventory() {
	return this->inventory;
}

