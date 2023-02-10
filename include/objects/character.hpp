#ifndef CHARACTER
#define CHARACTER

#include "../assets/hch.h"

#include "../assets/entity.hpp"
#include "../util/listUtils.hpp"
#include "../util/engine.hpp"
#include "item.hpp"
#include "inventory.hpp"
#include "../assets/weaponType.hpp"


class Character : public Entity{
    protected:
        int health;
        int max_health;
        int num_hearts;
        int damage;    //il danno che i suoi proiettili fanno ai mostri
        const char* projectile_icon;
        int projectile_moving_frequency;   //velocità proiettili che spara il personaggio
        int last_direction_taken;          //direzione in cui spara il personaggio
        Weapon weapon;

        List<Projectile> *projectilesList;
        List<SuperProjectile> *superProjectilesList;

		Inventory inventory;	//Inventario del personaggio
        
        
    public:
        Character();
        Character(const char * icon, Position pos, int max_health, const char * projectile_icon, int damage, int projectile_moving_frequency, WINDOW* win);
        void updateHearts();
        int getHearts();
        void updateHealth(int mod);
        void setHealth(int set);
        int getHealth();
        void setMaxHealth(int set);
        int getMaxHealth();
        void setDamage(int set);
        int getDamage();
        void setProjectileIcon(const char * set);
        const char * getProjectileIcon();
        void setProjectileMovingFrequency(int set);
        int getProjectileMovingFrequency();
        void setRoomWin(WINDOW* set);
        WINDOW* getRoomWin();
        int getLastDirection();
        void deleteIcon();
        void move(Position pos);
        void HandleInput(int input);
        bool legalMove(Position pos);
        bool steppedOnEnemy(Position pos);
        void shoot();
        void createProjectile(int direction, List<Projectile> *projectilesList);
        void createLaser(List<Projectile> *projectilesList);
        Weapon getWeapon();
        void setWeapon(Weapon weapon);
		void addToInventory(Item item);
		List<int> getInventory();
        void printInventory();
        void printInventoryTitle();
        void setProjectilesList(List<Projectile> *projectilesList);
        List<Projectile>* getProjectilesList();
        void setSuperProjectilesList(List<SuperProjectile> *superProjectilesList);
        List<SuperProjectile>* getSuperProjectilesList();
};

#endif