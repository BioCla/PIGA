#include "../../include/_init/game_loop.hpp"
#include "../../include/util/curses_comodity_functions.hpp"

#define CONTROL if(!state.paused)
#define charPos state.charStats.pos
#define sbgw state.board.getGameWindow()
#define sbiw state.board.getInfoWindow()


game Game::state;
bool Game::debugMode = false;
bool Game::debugFinished = false;

input Game::inputMap[] = {
	{ KEY_F(1), [] { debugMode = !debugMode; debugFinished = false; } },
	{ 'p', [] { pause(); } },
	{ 'q', [] { state.running = false; } },
};

debug_info Game::debugInfo[] = {
	{ "Status: ", [] { return state.paused ? "PAUSED " : "RUNNING"; } },
	{ "Score: ", [] { return std::to_string(state.score); } },
	{ "Dir: ", [] { return dirToString(charPos.dir); } },
	{ "Pos: ", [] { return "(" + std::to_string(charPos.currentPos.x) + ", " + std::to_string(charPos.currentPos.y) + ")\t"; } },
	{ "ET: ", [] { return std::to_string((float)(clock() - state.elapsed) / CLOCKS_PER_SEC); } },
	{ "FPS: ", [] { return std::to_string(state.fps); } },
	{ " ", [] { return ""; } },
};


Game::Game(Board board) {
	/* Stats */
	state.score = 0;
	state.running = true;
	state.paused = false;
	state.elapsed = clock();
	state.board = board;
	
	/* Player */
	charPos = { CENTER_POINT(sbgw), CENTER_POINT(sbgw), RIGHT };
	player = Player(entityInfo{
		charPos, true, 100, 10, 100, "@", sbgw, COLOR_WHITE, COLOR_WHITE
	});

	/* Debug */
	debugMode = false;
	debugFinished = false;
	debugWin = newwin(sizeof(debugInfo) / sizeof(debugInfo[0]) + 2, 24, sbgw->_begy + 1, sbgw->_begx + 1);
	wbkgd(debugWin, getbkgd(sbgw));
}

void Game::start() {
	nodelay(stdscr, true);
	timeMgmt timeManager;

	/**
	 * Iteration variables, keep track of numbers used in FPS calculation
	 * and performance measurements
	*/
	long long elapsedTime = 0;
	long long numIterations = 0;
	int ch;

	do {
		ch = getch();
		handleInput(ch);
		
		render();
		updateDebugWin();
		wrefresh(sbgw);
		
		timeManager.update_cycles_per_second(elapsedTime, numIterations, state.fps);
	} while (state.running == true);
	
	nodelay(stdscr, false);
}

void Game::pause() {
	state.paused = !state.paused;
	if (state.paused) {
		centering_text(sbiw, 0, "PAUSED");
		wrefresh(sbiw);
	} else {
		wclear(sbiw);
		box(sbiw, 0, 0);
		wrefresh(sbiw);
	}
}

inline void Game::render() {
	/* Player rendering / Updating local game stats */
	player.render();
	charPos = player.getPosition();
}

void Game::debugStats() {
	if (debugWin != NULL) {
		int y = 1;
		for (const debug_info& info : debugInfo) {
			mvwprintw(debugWin, y++, 1, "%s%s", info.label.c_str(), info.value().c_str());
		}
	}
}

void Game::handleInput(int ch) {
	if (ch == ERR) return;
	for (const input& in : inputMap) {
		if (ch == in.key) {
			HANDLE_INPUT(in);
			return;
		}
	}
	CONTROL
	player.inputHandler(ch);
}

inline void Game::updateDebugWin() {
	if (debugMode) {
		box(debugWin, 0, 0);
		debugStats();
		wrefresh(debugWin);	
	} else if (!debugFinished) {
		wclear(debugWin);
		wrefresh(debugWin);
		debugFinished = true;
	}
}