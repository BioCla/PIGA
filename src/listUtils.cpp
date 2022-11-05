#include "../lib/listUtils.hpp"
#include <cstddef>

List::List() {
    Entity default_entity = Entity();
    ent = default_entity;
    next = NULL;
}

List::List(Entity entry) {
    ent = entry;
    next = NULL;
}

bool List::isEmpty(plist head){
    return (head==NULL);
}

plist *createEmptyList(){
    return (NULL);
}
// ritorna il numero di elementi di una lista
int List::listLenght(plist head){
    plist tmp=head;
    int k=0;
    while(tmp!=NULL){
        tmp=tmp->next;
        k++;
    }
    return k;
}

plist List::headInsert(plist head, Entity entity){
    plist tmp = new List;
    tmp->next=head;
    tmp->ent=entity;
    return tmp;
}

plist List::tailInsert(plist head, Entity entity){
    if (head==NULL){
        head = new List;
        head->next=NULL;
        head->ent=entity;
    }
    else{
        plist tmp = head;
        while (tmp->next!=NULL) tmp=tmp->next;
        tmp->next = new List;
        tmp=tmp->next;
        tmp->next=NULL;
        tmp->ent=entity;
    }
}

plist List::removeFromList(plist head, Entity *entity){
    if (head==NULL) return head;
    else if (&head->ent==entity){
        plist tmp=head->next;
        delete head;
        return tmp;
    }
    else{
        bool flag=false;
        plist tmp = head;
        plist tmpafter = head->next;
        while((!flag) && (tmpafter!=NULL)){
            if(&tmpafter->ent==entity){
                tmp->next=tmpafter->next;
                flag = true;
                delete tmpafter;
            }
            else{
                tmp = tmpafter;
                tmpafter = tmpafter->next;
            }
        }
    }
    return (head);
}


