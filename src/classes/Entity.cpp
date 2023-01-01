#include "../../include/classes/Entity.hpp"

#define prevPos stats.pos.previousPos
#define currPos stats.pos.currentPos

entityInfo Entity::stats;

/* This should ever only be used for debugging and for inheritence */

Entity::Entity() {
	stats = {
		{ { 0, 0 }, { 0, 0 }, UP }, // pos
		true, // alive
		0, // health
		10, // damage
		0, // maxHealth
		"E", // icon
		stats.gameBoard, // gameBoard
		COLOR_WHITE, // fgColor
		COLOR_BLACK, // bgColor
	};
}

Entity::Entity(entityInfo initStats) {
	stats = initStats;
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
	} else {
		delete this;
	}
}

bool Entity::legalMove(point pos) {
    if ((mvwinch(GW, pos.y, pos.x) & A_CHARTEXT) == PAVE)
		return true;
	return false;
}