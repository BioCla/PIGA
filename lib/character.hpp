#include <ncursesw/ncurses.h>

#include "../assets/position.hpp"
#include "../assets/projList.hpp"

class Character {
    protected:
	// consiglio di convertire  l'utilizzo di `const char*` a `chtype` per ovviare a problemi di compatibilita' nelle funzioni di ncurses
	// Basta cambiare qualche tipo e le `""` in `''`
        const char* icon;
        int health;
        int max_health;
        int num_hearts;   //se vogliamo far vedere i cuori invece che il numero, come nell'esempio del prof
        //allora attenzione: io ho pensato che il personaggio ha 30 di vita e 3 cuori (uno x 10 pv) si può naturalmente cambiare ma fatelo con criterio
        int damage;    //il danno che i suoi proiettili fanno ai mostri
        const char* projectile_icon;
        int projectile_moving_frequency;
        Position current_position;
        WINDOW* current_room_win;
        int last_direction_taken;
        projList *projListHead;

        //inventario?
        //velocità?
        //velocità proiettili?

        //room_corrente: forse potrebbe convenire avere un puntatore all'oggetto room in cui si trova il personaggio

    public:
        Character();
        Character(int x, int y, const char * icon, int max_health, const char * projectile_icon, int projectile_moving_frequency);
        void updateHearts();
        void updateHealth(int mod);
        void setHealth(int set);
        int getHealth();
        void setDamage(int set);
        int getDamage();
        void setIcon(const char* set);
        const char* getIcon();
        void setProjectileIcon(const char * set);
        const char * getProjectileIcon();
        void setProjectileMovingFrequency(int set);
        int getProjectileMovingFrequency();
        void setRoomWin(WINDOW* set);
        WINDOW* getRoomWin();
        int getLastDirection();
        void PlayerMove(int x, int y);
        Position getCurrentPosition();
        void HandleInput(int input);
        bool legalMove(int posx, int posy);
        bool steppedOnEnemy(int posx, int posy);
        bool steppedOnArtifact(int posx, int posy);
        void shoot();
        void createProjectile(int direction);
        projList* getProjectilesShot();
};