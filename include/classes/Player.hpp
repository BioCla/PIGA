#include "Entity.hpp"

class Player : public Entity {
	private:
		static input inputMap[];

	public:
		Player() : Entity() {};
		Player(entityInfo stats) : Entity(stats) {};
		void inputHandler(int ch);
		entityPos getPosition();
		int health(bool mode);
		void renderStats();
		void render();
		bool legalMove(point pos);
};