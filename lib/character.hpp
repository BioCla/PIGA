#ifndef CHARACTER
#define CHARACTER

#include "../assets/hch.h"

#include "entity.hpp"
#include "../assets/projList.hpp"
#include "listUtils.hpp"
#include "engine.hpp"
#include "board.hpp"


class Character : public Entity{
    protected:
        int health;
        int max_health;
        int num_hearts;   //se vogliamo far vedere i cuori invece che il numero, come nell'esempio del prof
        //allora attenzione: io ho pensato che il personaggio ha 30 di vita e 3 cuori (uno x 10 pv) si può naturalmente cambiare ma fatelo con criterio
        int damage;    //il danno che i suoi proiettili fanno ai mostri
        const char* projectile_icon;
        int projectile_moving_frequency;
        int last_direction_taken;
        projList *projListHead;
        List<Projectile> projectilesCharacter;

        //inventario?
        //velocità?


    public:
        Character();
        Character(const char * icon, Position pos, int max_health, const char * projectile_icon, int projectile_moving_frequency, WINDOW* win);
        void updateHearts();
        void updateHealth(int mod);
        void setHealth(int set);
        int getHealth();
        void setDamage(int set);
        int getDamage();
        void setProjectileIcon(const char * set);
        const char * getProjectileIcon();
        void setProjectileMovingFrequency(int set);
        int getProjectileMovingFrequency();
        void setRoomWin(WINDOW* set);
        WINDOW* getRoomWin();
        int getLastDirection();
        void move(int x, int y);
        void HandleInput(int input);
        bool legalMove(int posx, int posy);
        bool steppedOnEnemy(int posx, int posy);
        bool steppedOnArtifact(int posx, int posy);
        void shoot();
        void createProjectile(int direction);
        projList* getProjectilesShot();
        List<Projectile> getNuovaListaProiettili();
};

#endif