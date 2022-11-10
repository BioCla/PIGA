#include "../lib/item.hpp"

Item::Item(int ID, Position pos, WINDOW* win) : Entity("",pos,win){
    this->ID=ID;
    switch (ID){
        case 1:
            this->icon="M";
            break;
        case 2:
            this->icon="N";
            break;
        case 3:
            this->icon="O";
            break;
    }
}

int Item::getID(){
    return ID;
}