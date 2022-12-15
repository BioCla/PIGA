#ifndef PROJECTILES
#define PROJECTILES

#include "../assets/hch.h"
#include "../assets/entity.hpp"
#include <chrono>
using namespace std::chrono;


class Projectile : public Entity {
    protected:
        int direction;
        int moving_frequency_multiplyer;
        duration <int, std::ratio <1,1000 > > moving_frequency;
        system_clock::time_point last_time_moved;
        int damage;   //danno che fa a chi colpisce, dipende da chi viene sparato
        bool isAllied; //true if the bullet comes from the character, false if it comes from an enemy

    public:
        Projectile();
        Projectile(const char* icon, Position position, int direction,int damage, int moving_frequency, bool isAllied, WINDOW* win);
        void spawn(Position initial_position);
        void deleteIcon();
        void setPosition(Position set);
        void move();
        void checkIfTimeToMove(system_clock::time_point time_now);
        bool collisionWithRoomWall(int posx, int posy);
        bool outOfBorder();
        bool checkifAllied();
        void setDamage(int damage);
        int getDamage();
};

#endif