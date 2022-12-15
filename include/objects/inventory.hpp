#include "../util/listUtils.hpp"
#include "item.hpp"

class Inventory {
	private:
		List<Item> inventory;
		WINDOW* inventoryWin;
	public:
		Inventory();
		void addToInventory(Item item);
		void removeFromInventory(int& tracker); // Rimuove un item dall'inventario (utilizza un tracker per identificare la posizione del item)
		List<int> getInventory(); // Ritorna l'inventario come un array di interi
};