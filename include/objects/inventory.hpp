#include "../util/listUtils.hpp"
#include "item.hpp"

class Inventory {
	private:
		List<Item> inventory;
		WINDOW* inventoryWin;
	public:
		Inventory();
		void addToInventory(Item item);
		List<int> getInventory(); // Ritorna l'inventario come un array di interi
		void printItems();
		void printTitle();
};