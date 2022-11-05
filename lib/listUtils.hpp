#ifndef LISTS
#define LISTS

#include "../lib/entity.hpp"

class List{
    protected:
        List *next;
        Entity ent;

    public:
    List();
    List(Entity entry);
    bool isEmpty(List* head);
    List* *createEmptyList();
    int listLenght(List* head);
    List* headInsert(List* head, Entity entity);
    List* tailInsert(List* head, Entity entity);
    List* removeFromList(List* head, Entity *entity);
};
typedef List *plist;

#endif