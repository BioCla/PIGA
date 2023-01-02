#include "../../include/util/curses_comodity_functions.hpp"
#include "../../include/_init/game_loop.hpp"

#include "../../include/util/adj_graph_override.tpp"

int main() {
	/* init();
	init_colorpairs();
	
	//Testing Colors
		empty();
		test_colors();
		getch();
		empty();

	// Testing GameBoard class
		Board main;
		// printScreenSize(main._window);

	// Testing GameLoop class
		Game loop(main);
		loop.start();
	
	
	endwin(); */

	// Testing Graphs
		Graph<float> graph;
		graph.AddVertex(0);
		graph.AddVertex(1);
		graph.AddVertex(2);
		graph.AddVertex(3);

		std::cout << graph[0] << std::endl;

		graph[0] = 5.00002f;
		std::cout << graph[0] << std::endl;

		graph.RemoveVertex(3);

		graph.AddEdge(0, 1);
		graph.AddEdge(0, 2);
		graph.AddEdge(1, 2);	

		std::cout << graph << std::endl;

		graph.RemoveEdge(0, 1);

		std::cout << graph << std::endl;
	return 0;
}