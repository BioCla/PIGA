#ifndef ADJ_GRAPH_OVERRIDE
#define ADJ_GRAPH_OVERRIDE

#include "listUtils.hpp"

template <typename T>
class Graph {
	protected:
		std::unordered_map<int, T> vertices_;
		std::unordered_map<int, List<int>> adjacency_lists_;
		int next_vertex_index_ = 0;
	
	public:
		Graph() {}
		void AddVertex(const T& data);
		void RemoveVertex(int index);
		void AddEdge(int u, int v);
		void RemoveEdge(int u, int v);
		bool HasEdge(int u, int v) const;
		const T& GetVertex(int index) const;
		void SetVertex(int index, const T& data);
		int NumVertices() const;
		int NumEdges() const;
		List<int> GetNeighbors(int index) const;

		const T& operator[] (int index) const {
			return GetVertex(index);
		}

		T& operator[] (int index) {
			return vertices_[index];
		}
};

#include "../../src/util/graph.ipp"

#endif