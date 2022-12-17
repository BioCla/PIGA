#include "curses_lib_selector.hpp"
#include "../_init/game_board.hpp"

enum direction {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	DEFAULT
};

/**
 * this is defined in "../../src/util/string_override.cpp"
*/ 
const char* dirToString(direction dir);

struct point {
	int x, y;
};

struct pointf {
	float x, y;
};

struct game {
	direction dir;
	point pos;
	int score;
	float fps;
	float speed;
	bool paused;
	Board board;
	bool running;
	clock_t elapsed;
	point previousPos;
};

enum itemType {
	BUFF,	// colore verde
	DEBUG,	// nessun colore
	DEBUFF,	// colore rosso
	WEAPON,	// colore blu
	ARTIFACT,	// colore giallo
};

struct itemProperties {
	int ID;
	itemType type;
	const char* name;
	const char* icon;
	const char* description;
};

struct input {
	int key;
	std::function<void()> instructions;
};

struct debug_info {
	std::string label;
	std::function<std::string()> value;
};

struct timeMgmt {
	SYS_CLOCK::time_point previousTime;
	SYS_CLOCK::time_point currentTime;
	TIME_DURATION elapsed;

	void update_time() {
		currentTime = SYS_CLOCK::now();
		elapsed = currentTime - previousTime;
		previousTime = currentTime;
	}

	/**
	 * @brief: calculates the number of cycles per second of a loop
	 * 
	 * @param elapsedTime: time elapsed in nanoseconds
	 * @param numIterations: number of iterations
	 * @param cps: frames per second
	 * 
	 * @note by taking external variables as parameters allows to use this function
	 * to be used in different loops and to calculate the number of 
	 * cycles per second of each loop.
	 * 
	 * updating the reference variables passed as parameters in order
	 * to allow the usage of them to be used in other functions
	 * 
	 * @example read "../../src/_init/game_loop.cpp"
	*/
	void cycles_per_second(long long& elapsedTime, long long& numIterations, float& cps) {
	update_time();
	numIterations++;
	elapsedTime += elapsed.count();

	if (elapsedTime >= 1000000000) {
		cps = elapsedTime / float(numIterations);
		numIterations = 0;
		elapsedTime = 0;
	}
}
};