#ifndef ITEM_LIST
#define ITEM_LIST

#include "../classes/Player.hpp"

/* Note:
	Items are entities and require the same struct as entities 
	as well as their own Item Properties and a working effect function:

	Entity Properties:
		struct entityPos {
			point currentPos;
			point previousPos;
			direction dir;
		};

		struct entityInfo {
			entityPos pos; // default: { {0, 0}, {0, 0}, RIGHT }
			bool alive; // default: true
			int health; 
			int damage; 
			int maxHealth;
			const char* icon; 
			Board gameBoard; 
			int fgColor;
			int bgColor;
		};

	Item Properties:
		struct itemProperties {
			itemType type;
			const char* name;
			const char* description;
		};
		std::function<void(Player)> effect;
*/

#include "game_structures.hpp"

/* 
	X(entityInfo, itemProperties, effect)

	"#", "Test", "Test", DEBUG, [](Player target) { target.heal(10); }
*/

#define IL \



#endif