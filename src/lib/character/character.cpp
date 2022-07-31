#include "character.hpp"

Character::Character() {
    icona = '@';
    max_salute = 30;
    salute = max_salute;
}

void Character::aggiornaCuori() {
    num_cuori = ((salute + 9) / 10);
}
/* in questo modo:
salute    num_cuori
30...........3
29...........3
21...........3
20...........2
11...........2
10...........1
5............1
1............1
0............0
*/



