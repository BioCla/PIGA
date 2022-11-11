#include "../lib/superProjectile.hpp"
#include "../lib/engine.hpp"

SuperProjectile::SuperProjectile() {
    icon = "-";
    current_position = {1, 1};
    direction = DIR_EAST;
    //a caso, giusto per vederlo vagare sullo schermo
    alive = true;
    current_room_win = stdscr;
}

SuperProjectile::SuperProjectile(const char* icon, Position position, int direction, int moving_frequency, int spawning_frequency,
                                int child_moving_frequency, const char* child_icon, WINDOW* win) : Projectile(icon, position, direction, moving_frequency, win) {


   
    duration <int, std::ratio <1,1000 > > one_millisecond (1);
    last_time_moved = system_clock::now();
    spawning_frequency_multiplyer = spawning_frequency;
    this->spawning_frequency = spawning_frequency_multiplyer * one_millisecond;
    if((direction == DIR_NORTH) || (direction == DIR_SOUTH)) spawning_axis = HORIZONTAL;
    else if ((direction == DIR_EAST) || (direction == DIR_WEST)) spawning_axis = VERTICAL;
    child_moving_frequency_multiplyer = child_moving_frequency;
    this->child_moving_frequency = child_moving_frequency_multiplyer * one_millisecond;
    this->child_icon = child_icon;

}

void SuperProjectile::shootProjectiles(projList* projListHead) {
    //projList *p1 = new projList;
    //projList *p2 = new projList;
    if(spawning_axis == VERTICAL) {
        createProjectile(DIR_NORTH, projListHead);
        createProjectile(DIR_SOUTH, projListHead);
    }
    else if(spawning_axis == HORIZONTAL) {
        createProjectile(DIR_EAST, projListHead);
        createProjectile(DIR_WEST, projListHead);
    }
}

void SuperProjectile::createProjectile(int direction, projList* projListHead) {
    projList *p = new projList;
    Projectile newProjectile = Projectile(child_icon, current_position, direction, child_moving_frequency_multiplyer, current_room_win);

    //head insert del nuovo proiettile
    p->next = projListHead;
    p->proj = newProjectile;

    //stampa il proiettile
    p->proj.move(); 

    projListHead = p;
}

bool SuperProjectile::checkIfTimeToShoot(system_clock::time_point time_now, projList* projListHead) {
    bool is_time = false;
    if(time_now > last_time_shot + spawning_frequency) {
        last_time_shot = time_now;
        //shootProjectiles(projListHead);
        is_time = true;
    }
    return is_time;
}

const char* SuperProjectile::getChildIcon() {
    return child_icon;
}

void SuperProjectile::getSpawningDirections(int directions[2]) {
    if(spawning_axis == VERTICAL) {
        directions[0] = DIR_NORTH;
        directions[1] = DIR_SOUTH;
    }
    else if(spawning_axis == HORIZONTAL) {
        directions[0] = DIR_EAST;
        directions[1] = DIR_WEST;
    }
}

int SuperProjectile::getChildMovingFrequency() {
    return child_moving_frequency_multiplyer;
}