#include "curses_lib_selector.hpp"
#include "../_init/game_board.hpp"

enum direction {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	DEFAULT
};

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
};