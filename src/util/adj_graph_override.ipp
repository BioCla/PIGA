template<typename T>
void Graph<T>::AddVertex(const T& data) {
	vertices_[next_vertex_index_] = data;
	adjacency_lists_[next_vertex_index_] = List<int>();
	next_vertex_index_++;
}

template<typename T>
void Graph<T>::RemoveVertex(int index) {
	vertices_.erase(index);
	adjacency_lists_.erase(index);
	for (auto& adjacency_list : adjacency_lists_)
		adjacency_list.second.remove(index);
}

template<typename T>
void Graph<T>::AddEdge(int u, int v) {
	if (HasEdge(u, v)) return;
	if (adjacency_lists_.find(u) == adjacency_lists_.end() || adjacency_lists_.find(v) == adjacency_lists_.end())
		return;
	adjacency_lists_[u].push_back(v);
	adjacency_lists_[v].push_back(u);
}

template<typename T>
void Graph<T>::RemoveEdge(int u, int v) {
	if (adjacency_lists_.find(u) == adjacency_lists_.end() || adjacency_lists_.find(v) == adjacency_lists_.end())
		return;
	adjacency_lists_[u].remove(v);
	adjacency_lists_[v].remove(u);
}

template<typename T>
bool Graph<T>::HasEdge(int u, int v) const {
	if (adjacency_lists_.find(u) == adjacency_lists_.end() || adjacency_lists_.find(v) == adjacency_lists_.end())
		return false;
	return adjacency_lists_.at(u).contains(v);
}

template<typename T>
const T& Graph<T>::GetVertex(int index) const {
	return vertices_.at(index);
}

template<typename T>
void Graph<T>::SetVertex(int index, const T& data) {
	vertices_[index] = data;
}

template<typename T>
int Graph<T>::NumVertices() const {
	return vertices_.size();
}

template<typename T>
int Graph<T>::NumEdges() const {
	int num_edges = 0;
	for (auto& adjacency_list : adjacency_lists_)
		num_edges += adjacency_list.second.size();
	return num_edges / 2;
}

template<typename T>
List<int> Graph<T>::GetNeighbors(int index) const {
	return adjacency_lists_.at(index);
}