#include "Entity.hpp"
#include "Projectile.hpp"

/* Pathing */
enum pathing {
	LINEAR, // Move in a straight line in a given direction
	TRACKING, // Move towards the player
	STATIC, // Don't move
};

struct enemyStats {
	pathing path;
	SYS_CLOCK::time_point _move;
	SYS_CLOCK::time_point _shot;
	List<Projectile> projectiles;
};

class Enemy: public Entity {
	private:
		enemyStats eStats;
		void shootProjectile(direction dir);

	public:
		Enemy() : Entity() {};
		Enemy(entityInfo stats) : 
			Entity(stats) {
				eStats.path = LINEAR;
				eStats._move = SYS_CLOCK::now();
				eStats._shot = SYS_CLOCK::now();
				stats.fgColor = COLOR_RED; stats.bgColor = COLOR_RED;
			};
};