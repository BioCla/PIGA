#ifndef ITEMS
#define ITEMS

#include "../assets/hch.h"
#include "entity.hpp"

class Item : public Entity{
    protected:
        int ID;
    public:
        Item(int ID, Position pos, WINDOW* win);
        int getID();
};

#endif