class Enemy { // i vari tipi di nemici saranno sottoclasse di questa classe
    protected:
        char icon;
        int health;
        int max_health;
        int damage;       //danno che infligge il nemico al giocatore
        //

    public:
        Enemy();
        void setHealth(int set);
        int getHealth();
        void setDamage(int set);
        int getDamage();
};