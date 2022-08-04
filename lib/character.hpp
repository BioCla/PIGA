#include <ncursesw/ncurses.h>

struct Position {
    int x;
    int y;
};

class Character {
    protected:
        const char* icon;
        int health;
        int max_health;
        int num_hearts;   //se vogliamo far vedere i cuori invece che il numero, come nell'esempio del prof
        int damage;    //il danno che i suoi proiettili fanno ai mostri
        char projectile_icon;
        Position current_position;
        WINDOW *win;

        //inventario?
        //velocità?
        //velocità proiettili?

    public:
    Character();
    Character(int x, int y);
    void updateHearts();
    void updateHealth(int mod);
    void setHealth(int set);
    int getHealth();
    void setDamage(int set);
    int getDamage();
    void setProjectileIcon(char set);
    char getProjectileIcon();
    void PlayerMove(int x, int y);
    Position getCurrentPosition();
    void HandleInput(int input);

};