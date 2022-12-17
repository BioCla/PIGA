#include "../../include/assets/game_structures.hpp"

#define HANDLE_INPUT(input) (((input).instructions)())

class Game {
	protected: 
		WINDOW* debugWin;
		static game state;
		static bool debugMode;
		static bool debugFinished;
		static input inputMap[];
		static debug_info debugInfo[];

	public:
		Game(Board board);
		void start();
		static void pause();
		void render();
		void debugStats();
		void updateDebugWin();
		void handleInput(int ch);
};