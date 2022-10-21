#include "../lib/superProjectile.hpp"
#include "../lib/engine.hpp"

SuperProjectile::SuperProjectile() {
    icon = "-";
    current_position = {1, 1};
    direction = DIR_EAST;     
    //a caso, giusto per vederlo vagare sullo schermo
    alive = true;
    head = NULL;
}

SuperProjectile::SuperProjectile(const char* icon, Position position, int direction, int moving_frequency, int spawning_frequency,
                                int spawning_axis, int child_moving_frequency) {
    this->icon = icon;
    current_position = position;
    this->direction = direction;
    moving_frequency_multiplyer = moving_frequency;
    duration <int, std::ratio <1,1000 > > one_millisecond (1);
    this->moving_frequency = moving_frequency_multiplyer * one_millisecond;
    last_time_moved = system_clock::now();
    alive = true;
    spawning_frequency_multiplyer = spawning_frequency;
    this->spawning_frequency = spawning_frequency_multiplyer * one_millisecond;
    head = NULL;
    this->spawning_axis = spawning_axis;
    moving_frequency_multiplyer = child_moving_frequency;
    this->child_moving_frequency = child_moving_frequency_multiplyer * one_millisecond;
}

void SuperProjectile::shootProjectiles() {
    if(spawning_axis == VERTICAL) {
        createProjectile(DIR_NORTH);
        createProjectile(DIR_SOUTH);
    }
    else if(spawning_axis == HORIZONTAL) {
        createProjectile(DIR_EAST);
        createProjectile(DIR_WEST);
    }
}

void SuperProjectile::createProjectile(int direction) {
    projList *p = new projList;
    Projectile newProjectile = Projectile(icon, current_position, direction, child_moving_frequency_multiplyer);
    
    //head insert del nuovo proiettile
    p->next = head;
    p->proj = newProjectile;
    
    //salva la nuova head
    head = p;

    //stampa il proiettile
    head->proj.moveProjectile();
}
