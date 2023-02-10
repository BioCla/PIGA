#ifndef LISTS_SPEC
#define LISTS_SPEC

#include "../../include/objects/enemy.hpp"
#include "../../include/objects/projectile.hpp"
#include "../../include/objects/superProjectile.hpp"



template <> void inline List<Enemy>::refreshEnemyTarget(Position p1){
    Node<Enemy> *tmp = this->head;
    while (tmp!=NULL) {
        tmp->data.setShootingTarget(p1);
        tmp=tmp->next;
    }

}

template class List<Enemy>;
template class List<Projectile>;
template class List<SuperProjectile>;
#endif