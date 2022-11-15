#ifndef ENEMIES
#define ENEMIES

#include "../assets/hch.h"
#include "entity.hpp"
#include "board.hpp"
#include "engine.hpp"
#include "projectile.hpp"
#include "listUtils.hpp"
#include <chrono>
using namespace std::chrono;

#define RANDOM 0
#define STSLR 1
#define STSUD 2 
#define CHASE 3

class Enemy : public Entity { // i vari tipi di nemici saranno sottoclasse di questa classe
    protected:
        int health;
        int max_health;
        int damage;       //danno che infligge il nemico al giocatore
        int pathing;
        int pathID; // percorso che fa il nemico (pathID =1 un pattern, pathID = 2 un altro pattern)[da cambiare]
        duration <int, std::ratio <1,1000 > > idle_time;
        system_clock::time_point last_time_moved;
        system_clock::time_point last_time_shot;
        List<Projectile> projlist;
        //Position distanceToPlayer;
        //

    public:
        Enemy();
        Enemy(const char* icon, int max_health, int damage, Position spawn_position, int pathID, duration <int, std::ratio <1,1000> > idle_time,WINDOW* win);
        void spawn(Position initial_position);
        void setHealth(int set);
        int getHealth();
        void setDamage(int set);
        int getDamage();
        void updateHealth(int mod);
        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();
        void move();
        void shoot();
        bool legalMove(int posx, int posy);
        void checkIfTimeToMove(system_clock::time_point time_now);
        void checkIfTimeToShoot(system_clock::time_point time_now);
        void setDistanceToPlayer(Position player_pos);
};

#endif