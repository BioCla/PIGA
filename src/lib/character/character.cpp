#include "character.hpp"

Character::Character() {
    icona = '@';
    max_salute = 30;
    salute = max_salute;
    danno = 5;   //numero a caso
    icona_proiettile = '-';
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

//si possono mettere valori negativi per far prendere danno al personaggio
void Character::modificaSalute(int mod) {
    salute = salute + mod;
}

void Character::setSalute(int set) {
    salute = set;
}

int Character::getSalute() {
    return salute;
}

void Character::setDanno(int set) {
    danno = set;
}

int Character::getDanno() {
    return danno;
}

void Character::setIconaProiettile(char set) {
    icona_proiettile = set;
}

char Character::getIconaProiettile() {
    return icona_proiettile;
}
