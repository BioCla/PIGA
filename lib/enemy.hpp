#include "../assets/hch.h"
#include "entity.hpp"
#include "../assets/position.hpp"
#include <chrono>
using namespace std::chrono;

class Enemy : public Entity { // i vari tipi di nemici saranno sottoclasse di questa classe
    protected:
        //--WINDOW* current_room_win;
        //--const char* icon;
        int health;
        int max_health;
        int damage;       //danno che infligge il nemico al giocatore
        //--Position current_position;
        int pathID; // percorso che fa il nemico (pathID =1 un pattern, pathID = 2 un altro pattern)[da cambiare]
        duration <int, std::ratio <1,1000 > > idle_time;
        system_clock::time_point last_time_moved;
        //

    public:
        Enemy();
        Enemy(const char* icon, int max_health, int damage, Position spawn_position, int pathID, duration <int, std::ratio <1,1000> > idle_time);
        void spawn(Position initial_position);
        void setHealth(int set);
        int getHealth();
        void setDamage(int set);
        int getDamage();
        void move();
        bool legalMove(int posx, int posy);
        void checkIfTimeToMove(system_clock::time_point time_now);
};