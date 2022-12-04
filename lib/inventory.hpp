#include "listUtils.hpp"
#include "item.hpp"

class Inventory {
	private:
		List<Item> inventory;
		WINDOW* inventoryWin;
	public:
		Inventory(); // Costruttore
		void addToInventory(Item item); // Aggiunge un item all'inventario
		void removeFromInventory(int& tracker); // Rimuove un item dall'inventario (utilizza un tracker per identificare la posizione del item)
		int* getInventory(); // Ritorna l'inventario
		void printInventory(); // Stampa l'inventario
};