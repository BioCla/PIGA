#ifndef LISTS_SPEC
#define LISTS_SPEC

template <typename T> void List<T>::moveEntities(system_clock::time_point time_now){
    Node<T> *tmp = this->head;
    while (tmp!=NULL) {
        tmp->data.checkIfTimeToMove(time_now);
        tmp=tmp->next;
    }    
}

template <typename T> void List<T>::removeDeadEntities(){
    if (head==NULL) return;
    else if((head->next==NULL)&&(!head->data.isAlive())){
        head->data.deleteIcon();
        delete head;
        head = NULL;
    }
    else{
        Node<T> *tmp = head;
        Node<T> *tmpafter = head->next;
        while(tmpafter!=NULL){
            if(!tmpafter->data.isAlive()){
                tmp->next = tmpafter->next;
                tmpafter->data.deleteIcon();
                delete tmpafter;
            }
            else{
                tmp = tmpafter;
            }
                tmpafter = tmp->next;
        }
        if (!head->data.isAlive()){
            Node<T> *tmp = head->next;
            head->data.deleteIcon();
            delete head;
            head=tmp;
        }

    }
}

template <> void inline List<Enemy>::spawnEnemies(){
    Node<Enemy> *tmp = this->head;
    while (tmp!=NULL) {
        tmp->data.spawn(tmp->data.getCurrentPosition());
        tmp=tmp->next;
    }
}

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





template class List<Enemy>;
template class List<Projectile>;
template class List<SuperProjectile>;
#endif