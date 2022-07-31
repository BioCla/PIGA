struct Position {
    int x;
    int y;
};

class Character {
    protected:
        char icona;
        int salute;
        int max_salute;
        int num_cuori;   //se vogliamo far vedere i cuori invece che il numero, come nell'esempio del prof
        int danno;    //il danno che i suoi proiettili fanno ai mostri
        char icona_proiettile;
        Position posizione_corrente;

        //inventario?
        //velocità?
        //velocità proiettili?

    public:
    Character();
    void aggiornaCuori();
    void modificaSalute(int mod);
    void setSalute(int set);
    int getSalute();
    void setDanno(int set);
    int getDanno();
    void setIconaProiettile(char set);
    char getIconaProiettile();
    void setPosizioneCorrente(Position set);
    Position getPosizioneCorrente();
};