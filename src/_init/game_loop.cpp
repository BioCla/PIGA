#include "../../include/_init/game_loop.hpp"
#include "../../include/util/curses_comodity_functions.hpp"

#define sdw state.currentWindow

game Game::state;
bool Game::debugMode = false;
bool Game::debugFinished = false;
float Game::fps = 0;

input Game::inputMap[] = {
	{ 265, [] { debugMode = !debugMode; debugFinished = false; } },
    { 'p', [] { state.paused = !state.paused; } },
    { 'q', [] { state.running = false; } },
};

debug_info Game::debugInfo[] = {
	{ "Status: ", [] { return state.paused ? "PAUSED" : "RUNNING"; } },
	{ "Score: ", [] { return std::to_string(state.score); } },
	{ "Direction: ", [] { return std::to_string(state.dir); } },
	{ "Speed: ", [] { return std::to_string(state.speed); } },
	{ "Position: ", [] { return "(" + std::to_string(state.pos.x) + ", " + std::to_string(state.pos.y) + ")"; } },
	{ "Elapsed time: ", [] { return std::to_string((float)(clock() - state.elapsed) / CLOCKS_PER_SEC); } },
	{ "FPS: ", [] { return std::to_string(fps); } },
};


Game::Game(WINDOW* win) {
	state.score = 0;
	state.dir = DOWN;
	state.speed = 0.5;
	state.running = true;
	state.paused = false;
	state.elapsed = clock();
	state.currentWindow = win;
	state.pos = {sdw->_maxy / 2, sdw->_maxx / 2};
	debugMode = false;
	debugFinished = false;
	debugWin = newwin(sizeof(debugInfo) / sizeof(debugInfo[0]) + 2, 24, sdw->_begy + 1, sdw->_begx + 1);
}

void Game::start() {
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
		wrefresh(state.currentWindow);
	
		if (elapsedTime >= 1000000000) {
			fps = elapsedTime / float(numIterations);
			numIterations = 0;
			elapsedTime = 0;
		}
	} while (state.running == true);
}

void Game::pause() {
	state.paused = true;
}

void Game::render() {
	mvwprintw(state.currentWindow, state.pos.y, state.pos.x, "X");
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