#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "Entity.hpp"

class Projectile : public Entity {
	protected:
		bool friendly;
		SYS_CLOCK::time_point moveDiff;
		STD_DUR<int, std::ratio<1,1000>> frequency;

	public:

};

#endif