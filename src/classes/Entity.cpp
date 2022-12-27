#include "../../include/classes/Entity.hpp"
#include "../../include/util/math_override.tpp"

#define prevPos stats.pos.previousPos
#define currPos stats.pos.currentPos
#define GW stats.gameWindow

entityInfo Entity::stats;

/* This should ever only be used for debugging and for inheritence */

Entity::Entity() {
	GW = stdscr;
	stats.icon = "E";
	stats.damage = 10;
	stats.alive = true;
	stats.maxHealth = 100;
	stats.bgColor = COLOR_BLACK;
	stats.fgColor = COLOR_WHITE;
	stats.health = stats.maxHealth;
	stats.pos = { { 0, 0 }, { 0, 0 }, UP };
}

Entity::Entity(entityInfo initStats) {
	GW = initStats.gameWindow;
	stats.pos = initStats.pos;
	stats.icon = initStats.icon;
	stats.alive = initStats.alive;
	stats.damage = initStats.damage;
	stats.fgColor = initStats.fgColor;
	stats.bgColor = initStats.bgColor;
	stats.health = initStats.maxHealth;
	stats.maxHealth = initStats.maxHealth;
}

entityPos Entity::getPosition() {
	return stats.pos;
}

#define futPos (currPos + point::dirToPoint(dir))

void Entity::move(direction dir) {	
	if (legalMove(currPos + point::dirToPoint(dir))) {
		prevPos = currPos;
		currPos = currPos + point::dirToPoint(dir);
	}
}

int Entity::takeDamage(int amount) {
	stats.health -= amount;
	if (stats.health <= 0) {
		stats.alive = false;
	}
	return stats.health;
}

int Entity::heal(int amount) {
	stats.health += amount;
	if (stats.health > stats.maxHealth) {
		stats.health = stats.maxHealth;
	}
	return stats.health;
}

bool Entity::isAlive() {
	return stats.alive;
}

void Entity::render() {
	int GWPair = PAIR_NUMBER(GW->_attrs);
	setcolor(GW, dcantor(GWPair));
	mvwaddstr(GW, prevPos.y, prevPos.x, " ");
	unsetcolor(GW, dcantor(GWPair));  
	
	prevPos = currPos;
	if (stats.alive) {
		setcolor(GW, stats.fgColor, stats.bgColor);
		mvwaddstr(GW, currPos.y, currPos.x, stats.icon);
		unsetcolor(GW, stats.fgColor, stats.bgColor);
	}
}

bool Entity::legalMove(point pos) {
    return ((mvwinch(GW, pos.y, pos.x) & A_CHARTEXT) == PAVE);
}