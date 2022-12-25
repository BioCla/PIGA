#include "../classes/Player.hpp"
#include "game_board.hpp"

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
		Player player;
		WINDOW* debugWin;
		static game state;
		static bool debugMode;
		static bool debugFinished;
		static input inputMap[];
		static debug_info debugInfo[];
		void debugStats();
		static void pause(); // This needs to be `static` in order to be utilized in the `inputMap`
		inline void render();
		void handleInput(int ch);
		inline void updateDebugWin();

	public:
		Game(Board board);
		void start();
};