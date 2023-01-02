#include "../../include/assets/position.hpp"
#include <math.h>

bool compare(Position p1, Position p2){
    return ((p1.x==p2.x)&&(p1.y==p2.y));
}

double distance(Position p1, Position p2){
    return sqrt(pow((p1.x-p2.x),2)+pow((p1.y-p2.y),2));
}

Position dirToPosition(int dir) {
    switch (dir) {
        case DIR_NORTH:
            return {0, -1};
        case DIR_EAST:
            return {1, 0};
        case DIR_SOUTH:
            return {0, +1};
        case DIR_WEST:
            return {-1, 0};
        default:
            return {0, 0};
    }
}