#include <ncurses.h>
#include "../assets/position.hpp"


class Projectile {
    protected:
        WINDOW* proj_win;
        Position current_position;
        int direction;
        const char* icon;

        //direi che la convenzione dove partiamo da 0 nord e incrementiamo in senso orario può andare bene
        //0: nord   1:est   2:sud   3:ovest

    public:
        Projectile();
        Projectile(const char* icon, Position position, int direction);
        void spawn(WINDOW* win, Position initial_position);
        Position getCurrentPosition();
        void setPosition(Position set);
};