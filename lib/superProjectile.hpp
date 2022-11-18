#ifndef SUPERPROJECTILES
#define SUPERPROJECTILES

#include "../assets/projList.hpp"
#include "listUtils.hpp"
#include <chrono>
using namespace std::chrono;
#define VERTICAL 0
#define HORIZONTAL 1

typedef projList *p_projList;

class SuperProjectile : public Projectile {
    protected:
    int spawning_frequency_multiplyer;
    duration <int, std::ratio <1,1000 > > spawning_frequency;
    int spawning_axis;
    int child_moving_frequency_multiplyer;
    duration <int, std::ratio <1,1000 > > child_moving_frequency;
    system_clock::time_point last_time_shot;
    const char* child_icon;

    
    public:
    SuperProjectile();
    SuperProjectile(const char* icon, Position position, int direction, int moving_frequency, int spawning_frequency, 
                    int child_moving_frequency, const char* child_icon, WINDOW* win);
    void shootProjectiles(List<Projectile> *projList);
    void createProjectile(int direction, List<Projectile> *projList);
    void checkIfTimeToShoot(system_clock::time_point time_now, List<Projectile> *projList);
    const char* getChildIcon();
    void getSpawningDirections(int directions[2]);
    int getChildMovingFrequency();
};

#endif