#pragma once
#ifndef POSITION
#define POSITION

struct Position {
    int x;
    int y;
};

bool compare(Position p1, Position p2);
double distance(Position p1, Position p2);

#endif