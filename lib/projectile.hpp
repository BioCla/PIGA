#ifndef PROJECTILES
#define PROJECTILES

#include <ncursesw/ncurses.h>
#include "../assets/position.hpp"
#include <chrono>
using namespace std::chrono;


class Projectile {
    protected:
        WINDOW* current_room_win;
        const char* icon;
        Position current_position;
        int direction;
        int moving_frequency_multiplyer;
        duration <int, std::ratio <1,1000 > > moving_frequency;
        system_clock::time_point last_time_moved;
        bool alive;   //un proiettile è "vivo" se non si è scontrato con muri o altre cose. appena questa diventa fase il proiettile va eliminato
        

    public:
        Projectile();
        Projectile(const char* icon, Position position, int direction, int moving_frequency);
        void spawn(Position initial_position);
        void deleteIcon();
        void setPosition(Position set);
        Position getCurrentPosition();
        void setCurrentRoom(WINDOW* set);
        WINDOW* getCurrentRoom();
        void moveProjectile();
        void checkIfTimeToMove(system_clock::time_point time_now);
        bool collisionWithRoomWall(int posx, int posy);
        bool outOfBorder();
        bool isAlive();
        void setAliveStatus(bool set);
};

#endif