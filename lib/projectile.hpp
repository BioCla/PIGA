#include <ncursesw/ncurses.h>
#include "../assets/position.hpp"
#include <chrono>
using namespace std::chrono;

#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP
class Projectile {
    protected:
        WINDOW* current_room_win;
        const char* icon;
        Position current_position;
        int direction;
        int moving_frequency_multiplyer;
        duration <int, std::ratio <1,1000 > > moving_frequency;
        system_clock::time_point last_time_moved;

        //direi che la convenzione dove partiamo da 0 nord e incrementiamo in senso orario può andare bene
        //0: nord   1:est   2:sud   3:ovest

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
};

#endif