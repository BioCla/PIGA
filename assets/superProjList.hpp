#ifndef SUPERPROJLIST
#define SUPERPROJLIST

#include "../lib/superProjectile.hpp"

struct superProjList {
    SuperProjectile sproj;
    superProjList *next;
};


#endif