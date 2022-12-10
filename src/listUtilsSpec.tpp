#ifndef LISTS_SPEC
#define LISTS_SPEC

#include "../lib/enemy.hpp"
#include "../lib/projectile.hpp"
#include "../lib/superProjectile.hpp"

/*
template <> void inline List<Enemy>::spawnEnemies(){
    Node<Enemy> *tmp = this->head;
    while (tmp!=NULL) {
        tmp->data.spawn(tmp->data.getCurrentPosition());
        tmp=tmp->next;
    }
}
*/

template <> void inline List<Enemy>::refreshEnemyTarget(Position p1){
    Node<Enemy> *tmp = this->head;
    while (tmp!=NULL) {
        tmp->data.setShootingTarget(p1);
        tmp=tmp->next;
    }

}

template <> void inline List<Enemy>::refreshEnemyProj(system_clock::time_point time_now){
    Node<Enemy> *tmp = this->head;
    while (tmp!=NULL) {
        tmp->data.refreshProj(time_now);
        tmp=tmp->next;
    }  
}

//FUNZIONI DEBUG
template <> void inline List<Enemy>::killEnemy(int o){
    Node<Enemy> *tmp = this->head;
    int h=0;
    while(h!=o){
        tmp=tmp->next;
        h++;
    }
    tmp->data.updateHealth(-11);
}
/*
template <> void inline List<Entity>::spawnEntities(){
    Node<Entity> *tmp = this->head;
    while (tmp!=NULL) {
        tmp->data.spawn(tmp->data.getCurrentPosition());
        tmp=tmp->next;
    }
}
*/

template class List<Enemy>;
template class List<Projectile>;
template class List<SuperProjectile>;
#endif