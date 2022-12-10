#include "../assets/position.hpp"
#include <math.h>

bool compare(Position p1, Position p2){
    return ((p1.x==p2.x)&&(p1.y==p2.y));
}

double distance(Position p1, Position p2){
    return sqrt(pow((p1.x-p2.x),2)+pow((p1.y-p2.y),2));
}