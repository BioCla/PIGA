/*quali variabili mi potrebbero servire per una stanza:
Coordinata X del giocatore
Coordinata Y del giocatore
Numero di Porte (magari delle flag per gestire quali porte ci sono e quali no)
Numero di mob
Numero di oggetti ecc
*/
#include <iostream>
using namespace std;
struct Position{
    int x;
    int y;
};

class Room{
    protected:
    Position position;
    Position spawnpoint;
    bool NorthDoor;
    bool WestDoor;
    bool EastDoor;
    bool SouthDoor;

    public: 
    Room(int positionx, int positiony, int spawnx=0, int spawny=0, bool NorthDoor=false, bool WestDoor=false, bool EastDoor=false, bool SouthDoor=false){
        this->position.x=positionx;
        this->position.y=positiony;
        this->spawnpoint.x=spawnx;
        this->spawnpoint.y=spawny;
        this->NorthDoor=NorthDoor;
        this->EastDoor=EastDoor;
        this->SouthDoor=SouthDoor;
        this->WestDoor=WestDoor;
    }
    
    void setDoor(int choose, bool state){
        switch (choose){
            case 0: this->NorthDoor = state;
            case 1: this->EastDoor = state;
            case 2: this->SouthDoor = state;
            case 3: this->WestDoor = state;
        }
    }

    bool getDoor(int choose){
        bool flag;
        switch (choose){
            case 0: flag=this->NorthDoor;
            case 1: flag=this->EastDoor;
            case 2: flag=this->SouthDoor;
            case 3: flag=this->WestDoor;
        }
        return flag;
    }
};

struct node{
    Room room;
    node *next;
};

class linked_list{
    protected:
        node *head, *tail;

    public:
        linked_list(){
            head=NULL;
            tail=NULL;
        }

        void add_node (Room room){
            //node *tmp=new node;
            //tmp->room=room;
            //tmp->next=NULL;

        }
};




