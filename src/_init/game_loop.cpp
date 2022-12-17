#include "../../include/_init/game_loop.hpp"
#include "../../include/util/string_override.hpp"
#include "../../include/util/curses_comodity_functions.hpp"

#define sdw state.board.getGameWindow()
#define CONTROL if(!state.paused)

game Game::state;
bool Game::debugMode = false;
bool Game::debugFinished = false;

input Game::inputMap[] = {
	{ KEY_F(1), [] { debugMode = !debugMode; debugFinished = false; } },
    { 'p', [] { pause(); } },
    { 'q', [] { state.running = false; } },

	{ 'w', [] { CONTROL state.pos.y -= 1; } },
	{ 's', [] { CONTROL state.pos.y += 1; } },
	{ 'a', [] { CONTROL state.pos.x -= 1; } },
	{ 'd', [] { CONTROL state.pos.x += 1; } },

	{ KEY_UP, [] { CONTROL state.dir = UP; } },
	{ KEY_DOWN, [] { CONTROL state.dir = DOWN; } },
	{ KEY_RIGHT, [] { CONTROL state.dir = RIGHT; } },
	{ KEY_LEFT, [] { CONTROL state.dir = LEFT; } },
};

debug_info Game::debugInfo[] = {
	{ "Status: ", [] { return state.paused ? "PAUSED " : "RUNNING"; } },
	{ "Score: ", [] { return std::to_string(state.score); } },
	{ "Dir: ", [] { return dirToString(state.dir); } },
	{ "Speed: ", [] { return std::to_string(state.speed); } },
	{ "Pos: ", [] { return "(" + std::to_string(state.pos.x) + ", " + std::to_string(state.pos.y) + ")"; } },
	{ "ET: ", [] { return std::to_string((float)(clock() - state.elapsed) / CLOCKS_PER_SEC); } },
	{ "FPS: ", [] { return std::to_string(state.fps); } },
};


Game::Game(Board board) {
	state.score = 0;
	state.dir = UP;
	state.speed = 0.5;
	state.running = true;
	state.paused = false;
	state.elapsed = clock();
	state.board = board;
	state.pos = {sdw->_maxx / 2, sdw->_maxy / 2};
	state.previousPos = state.pos;
	debugMode = false;
	debugFinished = false;
	debugWin = newwin(sizeof(debugInfo) / sizeof(debugInfo[0]) + 2, 24, sdw->_begy + 1, sdw->_begx + 1);
}

void Game::start() {
	nodelay(stdscr, true);
	timeMgmt timeManager;
	long long elapsedTime = 0;
	long long numIterations = 0;

	do {
		timeManager.update_time();
		numIterations++;
		elapsedTime += timeManager.elapsed.count();

		int ch = getch();
		handleInput(ch);
		
		updateDebugWin();
		render();
		wrefresh(sdw);

		state.previousPos = state.pos;
	
		if (elapsedTime >= 1000000000) {
			state.fps = elapsedTime / float(numIterations);
			numIterations = 0;
			elapsedTime = 0;
		}
	} while (state.running == true);
	nodelay(stdscr, false);
}

void Game::pause() {
	state.paused = !state.paused;
	if (state.paused) {
		mvwaddstr(state.board.getInfoWindow(), 0, 1, "PAUSED");
		wrefresh(state.board.getInfoWindow());
	} else {
		box(state.board.getInfoWindow(), 0, 0);
		wrefresh(state.board.getInfoWindow());
	}
}

// This is just to test the game loop compability with character movement
void Game::render() {
	mvwaddch(sdw, state.previousPos.y, state.previousPos.x, ' ');
	mvwaddch(sdw, state.pos.y, state.pos.x, '@');
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
	for (const input& in : inputMap) {
		if (ch == in.key) {
			HANDLE_INPUT(in);
			break;
		}
	}
}

void Game::updateDebugWin() {
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