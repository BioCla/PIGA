#include "projectile.hpp"
#include "../assets/projList.hpp"
#include "../assets/position.hpp"
#include <chrono>
using namespace std::chrono;
#define VERTICAL 0
#define HORIZONTAL 1

class SuperProjectile : public Projectile {
    protected:
    projList* head;
    int spawning_frequency_multiplyer;
    duration <int, std::ratio <1,1000 > > spawning_frequency;
    int spawning_axis;
    int child_moving_frequency_multiplyer;
    duration <int, std::ratio <1,1000 > > child_moving_frequency;
    
    public:
    SuperProjectile();
    SuperProjectile(const char* icon, Position position, int direction, int moving_frequency, int spawning_frequency, 
                    int spawning_axis, int child_moving_frequency);
    void shootProjectiles();
    void createProjectile(int direction);
};
