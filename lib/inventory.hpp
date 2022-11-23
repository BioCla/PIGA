#include "listUtils.hpp"
#include "item.hpp"

class Inventory {
	private:
		List<Item> inventory;
	public:
		Inventory(); // Costruttore
		void addToInventory(Item item); // Aggiunge un item all'inventario
		void removeFromInventory(int& tracker); // Rimuove un item dall'inventario (utilizza un tracker per identificare la posizione del item)
		List<Item> getInventory(); // Ritorna l'inventario
};