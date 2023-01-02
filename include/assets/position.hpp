#pragma once
#ifndef POSITION
#define POSITION

#include "directions.hpp"

struct Position {
    int x;
    int y;

	friend Position operator+(const Position& p1, const Position& p2) {
		return {p1.x + p2.x, p1.y + p2.y};
	}
};

bool compare(Position p1, Position p2);
double distance(Position p1, Position p2);
Position dirToPosition(int dir);

#endif