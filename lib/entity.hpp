#ifndef ENTITY
#define ENTITY

#include "../assets/hch.h"
#include "../assets/position.hpp"


class Entity {
    protected:
        bool alive;
        const char* icon;
        Position current_position;
        WINDOW* current_room_win;


    public:
        Entity();
        Entity(const char* icon, Position initial_position, WINDOW* win);
        void setAlive(bool alive);
        bool isAlive();
        void setIcon(const char* new_icon);
        const char* getIcon();
        Position getCurrentPosition();
        void spawn();
        void spawn(Position position);
        void deleteIcon();
        void move(int new_pos_x, int new_pos_y);
        WINDOW* getWin();
        void setCurrentRoom(WINDOW* set);
      
};

#endif
