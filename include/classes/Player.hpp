#include "Entity.hpp"

class Player : public Entity {
	private:
		static input inputMap[];

	public:
		Player() : Entity() {};
		Player(entityInfo stats) : 
			Entity(stats) {
				stats.fgColor = COLOR_WHITE; stats.bgColor = COLOR_WHITE;
			};
		entityPos getPosition();
		void inputHandler(int ch);
};