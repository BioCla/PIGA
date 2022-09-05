#ifndef PROJLIST_HPP
#define PROJLIST_HPP

#include "../lib/projectile.hpp"

struct projList {
    Projectile proj;
    projList *next;
};

#endif