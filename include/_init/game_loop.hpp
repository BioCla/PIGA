#include "../classes/Player.hpp"

struct game {
	int score;
	float fps;
	bool paused;
	Board board;
	bool running;
	direction dir;
	clock_t elapsed;
	entityInfo charStats;
};

struct debug_info {
	std::string label;
	std::function<std::string()> value;
};

class Game {
	private: 
		static Player player;
		WINDOW* debugWin;
		static game state;
		static bool debugMode;
		static bool debugFinished;
		static input inputMap[];
		static debug_info debugInfo[];
		void debugStats();
		static void pause();
		inline void render();
		void handleInput(int ch);
		inline void updateDebugWin();

	public:
		Game(Board board);
		void start();
};