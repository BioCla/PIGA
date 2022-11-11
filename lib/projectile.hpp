#ifndef PROJECTILES
#define PROJECTILES

#include "../assets/hch.h"
#include "entity.hpp"
#include <chrono>
using namespace std::chrono;


class Projectile : public Entity {
    protected:
        //--WINDOW* current_room_win;
        //--const char* icon;
        //--Position current_position;
        int direction;
        int moving_frequency_multiplyer;
        duration <int, std::ratio <1,1000 > > moving_frequency;
        system_clock::time_point last_time_moved;
        //--bool alive;   //un proiettile è "vivo" se non si è scontrato con muri o altre cose. appena questa diventa fase il proiettile va eliminato
        

    public:
        Projectile();
        Projectile(const char* icon, Position position, int direction, int moving_frequency, WINDOW* win);
        void spawn(Position initial_position);
        void deleteIcon();
        void setPosition(Position set);
        void move();
        void checkIfTimeToMove(system_clock::time_point time_now);
        bool collisionWithRoomWall(int posx, int posy);
        bool outOfBorder();
};

#endif