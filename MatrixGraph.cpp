#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(int numberOfVertices, int startVertex) {
	this->size = numberOfVertices;
	this->graph = new int* [size];
	this->undirectedGraph = new int* [size];
	this->startVertex = startVertex;
	this->mst = new std::list<Edge>;
	this->edges = new std::priority_queue <Edge, std::vector<Edge>, CompareWeight>;

	for (int i = 0; i < size; i++) {
		this->graph[i] = new int[size];
		for (int j = 0; j < size; j++)
			this->graph[i][j] = INT_MAX; // nieskonczonosc
	}

	for (int i = 0; i < size; i++) {
		undirectedGraph[i] = new int[size];
		for (int j = 0; j < size; j++)
			undirectedGraph[i][j] = INT_MAX;
	}
}

bool MatrixGraph::addEdge(int v1, int v2, int weight) {
	if (v1 == v2 || v1 >= size || v2 >= size) return false;
	graph[v1][v2] = weight;

	undirectedGraph[v1][v2] = weight;
	undirectedGraph[v2][v1] = weight;

	return true;
}

MatrixGraph::~MatrixGraph() {
	for (int i = 0; i < size; i++)
		delete[] graph[i];
	delete[] graph;

	for (int i = 0; i < size; i++)
		delete[] undirectedGraph[i];
	delete[] undirectedGraph;

	delete edges;
	delete mst;

}

void MatrixGraph::display() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++)
			if (graph[i][j] == INT_MAX) std::cout << std::setw(4) << "-";
			else std::cout << std::setw(4) << graph[i][j];
		
		std::cout << std::endl;
	}
}

int MatrixGraph::kruskalFind(KruskalSet* sets, int vertex) {
	if (sets[vertex].parent != vertex)
		sets[vertex].parent = kruskalFind(sets, sets[vertex].parent);

	return sets[vertex].parent;
}

void MatrixGraph::kruskalUnion(KruskalSet* sets, int first, int second) {
	int firstRoot = kruskalFind(sets, first);
	int secondRoot = kruskalFind(sets, second);

	if (sets[firstRoot].rank < sets[secondRoot].rank) {
		sets[firstRoot].parent = secondRoot;
	}
	else if (sets[firstRoot].rank > sets[secondRoot].rank) {
		sets[secondRoot].parent = firstRoot;
	}
	else {
		sets[secondRoot].parent = firstRoot;
		sets[firstRoot].rank++;
	}
}

void MatrixGraph::kruskal() {

	// Wyluskuje krawedzie z macierzy i umieszczam w kolejce priorytetowej
	// rosnaco po wagach.

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (undirectedGraph[i][j] != INT_MAX) {
				Edge* edge = new Edge;
				edge->source = i;
				edge->target = j;
				edge->weight = undirectedGraph[i][j];
				(*edges).push(*edge);
			}
		}
	}

	KruskalSet* sets = new KruskalSet[size];

	for (int i = 0; i < size; i++) {
		sets[i].parent = i;
		sets[i].rank = 0;
	}

	int i = 0;
	while (i < size-1) {
		Edge e = (*edges).top();
		(*edges).pop();

		int beginOfSet = kruskalFind(sets, e.source);
		int endOfSet = kruskalFind(sets, e.target);

		if (beginOfSet != endOfSet) {
			kruskalUnion(sets, beginOfSet, endOfSet);
			(*mst).push_back(e);
			i++;
		}
	}

	delete[] sets;

	std::cout << "Edge: | Weight:" << std::endl;
	int cost = 0;

	for (Edge e : (*mst)) {
		std::cout << "(" << e.source << ":" << e.target << ") - " << e.weight << std::endl;
		cost += e.weight;
	}

	std::cout << std::endl << "MST = " << cost << std::endl;
	(*mst).clear();
}

int MatrixGraph::findEdge(int v1, int v2) {
	return graph[v1][v2];
}

int MatrixGraph::findEdge2(int v1, int v2) {
	return undirectedGraph[v1][v2];
}

void MatrixGraph::dikstra() {
	int* distance = new int[size];
	int* parent = new int[size];

	for (int i = 0; i < size; i++) {
		distance[i] = INT_MAX;	// nieskonczonosc
		parent[i] = -1;			// poprzednik
	}

	distance[startVertex] = 0;
	std::priority_queue <ListItem, std::vector<ListItem>, CompareWeight2> items;

	for (int i = 0; i < size; i++) {
		ListItem* item = new ListItem;
		item->vertex = i;
		item->weight = distance[i];
		items.push(*item);
	}

	while (!items.empty()) {
		ListItem item = items.top();
		items.pop();

		for (int i = 0; i < size; i++) {
			int weight = findEdge(item.vertex, i);

			if (weight < 0) {
				std::cout << "Wagi sa ujemne! Zmien wagi na dodatnie." << std::endl;
				return;
			}

			if (weight != INT_MAX) {
				if (distance[item.vertex] + weight < distance[i] && distance[item.vertex] != INT_MAX) {
					ListItem* item2 = new ListItem;
					item2->vertex = i;
					item2->weight = distance[i];
					distance[i] = distance[item.vertex] + weight;
					parent[i] = item.vertex;

					items.push(*item2);
					delete item2;
				}
			}
		}
	}

	int* Stack = new int[size];
	int ptr = 0;							   

	std::cout << "End:| " << "Dist:| " << "Path:  " << std::endl;

	for (int i = 0; i < size; i++){
		std::cout << " " << i << "  |   ";

		for (int j = i; j > -1; j = parent[j]) Stack[ptr++] = j;

		std::cout << distance[i] << "  | ";

		while (ptr)
			std::cout << Stack[--ptr] << " ";

		std::cout << std::endl;
	}

	delete[] distance;
	delete[] parent;
	delete[] Stack;
}