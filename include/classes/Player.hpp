#include "Entity.hpp"

class Player : public Entity {
	private:
		static input inputMap[];

	public:
		Player() : Entity() {};
		Player(entityInfo stats) : Entity(stats) {};
		entityPos getPosition();
		void inputHandler(int ch);
		void renderStats();
		void render();
};