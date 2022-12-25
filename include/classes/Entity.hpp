#include "../assets/game_structures.hpp"
#include "../util/curses_color_pairing.hpp"

struct entityPos {
	point currentPos;
	point previousPos;
	direction dir;
};

struct entityInfo {
	entityPos pos;
	bool alive;
	int health;
	int damage;
	int maxHealth;
	const char* icon;
	WINDOW* gameWindow;
	int fgColor;
	int bgColor;

	friend std::ostream& operator<<(std::ostream& out, const entityInfo& s) {
		out << "icon: " << s.icon << std::endl;
		out << "alive: " << s.alive << std::endl;
		out << "health: " << s.health << std::endl;
		out << "damage: " << s.damage << std::endl;
		out << "pos: " << s.pos.currentPos << std::endl;
		out << "maxHealth: " << s.maxHealth << std::endl;
		return out;
	}
};

class Entity {
	protected:
		static entityInfo stats;

	public:
		Entity();
		Entity(entityInfo stats);
		static void move(direction dir);
		int takeDamage(int amount);
		int heal(int amount);
		bool isAlive();
		entityPos getPosition();
		void render();
		static bool legalMove(point pos);
};