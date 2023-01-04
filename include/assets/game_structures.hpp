#ifndef GAME_STRUCTURES
#define GAME_STRUCTURES

#include "../util/curses_color_pairing.hpp"
#include "../util/math_override.tpp"

/* adv/debug */
#define HANDLE_INPUT(input) (((input).instructions)())
#define NULL_FUNC [](const auto& a) { std::cout << a << std::endl; }
#define CENTER_POINT(win) {win->_maxx / 2, win->_maxy / 2}
#define KEY_ESC 27

/* blocks */
#define WALL      '#'
#define PAVE      ' '

enum direction {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	DEFAULT
};

struct point {
	int x, y;

	friend std::ostream& operator<<(std::ostream& out, const point& p) {
		out << "(" << p.x << ", " << p.y << ")";
		return out;
	}

	friend std::string to_string(const point& p) {
		std::ostringstream ss;
		ss << p;
		return std::move(ss).str();
	}

	static inline point dirToPoint(direction dir) {
		switch (dir) {
			case UP:
				return {0, -1};
			case DOWN:
				return {0, 1};
			case LEFT:
				return {-1, 0};
			case RIGHT:
				return {1, 0};
			default:
				return {0, 0};
		}
	}

	friend point operator+(const point& p1, const point& p2) {
		return {p1.x + p2.x, p1.y + p2.y};
	}
};

struct input {
	int key;
	std::function<void()> instructions;
};

struct timeMgmt {
	SYS_CLOCK::time_point previousTime;
	SYS_CLOCK::time_point currentTime;
	TIME_DURATION elapsed;

	/* Using `inline` to improve functionality so that there are less calls to the stack and calling function */

	inline void update_time() {
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
	 * the result is stored in the variable cps, which should be provided as a reference
	 * 
	 * @example read "../../src/_init/game_loop.cpp"
	*/
	inline void update_cycles_per_second(long long& elapsedTime, long long& numIterations, float& cps) {
		update_time();
		numIterations++;
		elapsedTime += elapsed.count();

		if (elapsedTime >= 1000000000 /* One second in `ns` */) {
			cps = elapsedTime / float(numIterations);
			numIterations = 0;
			elapsedTime = 0;
		}
	}
};

enum itemType {
	DEBUFF = cantor(getCC(COLOR_VIB_RED), getCC(COLOR_VIB_RED)),
	BUFF = cantor(getCC(COLOR_VIB_GREEN), getCC(COLOR_VIB_GREEN)),
	WEAPON = cantor(getCC(COLOR_VIB_BLUE), getCC(COLOR_VIB_BLUE)),
	DEBUG = cantor(getCC(COLOR_VIB_MAGENTA), getCC(COLOR_VIB_MAGENTA)),
	ARTIFACT = cantor(getCC(COLOR_VIB_YELLOW), getCC(COLOR_VIB_YELLOW)),
};

/**
 * this is defined in "../../src/util/string_override.cpp"
*/ 
const char* dirToString(direction dir);
const char* itemTypeToString(itemType type);

#endif