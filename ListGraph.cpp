#include "ListGraph.h"

ListGraph::ListGraph(int size, int startVertex) {
	this->size = size;
	this->startVertex = startVertex;
	this->edges = new std::priority_queue <Edge, std::vector<Edge>, CompareWeight>;
	this->mst = new std::list<Edge>;

	list.resize(size);
	undirectedGraph.resize(size);
}

ListGraph::~ListGraph() {
	delete edges;
	delete mst;
}

bool ListGraph::addEdge(int v1, int v2, int weight) {
	if (v1 == v2 || v1 >= size || v2 >= size) return false;
	list[v1].push_back(std::make_pair(v2, weight));

	undirectedGraph[v1].push_back(std::make_pair(v2, weight));
	undirectedGraph[v2].push_back(std::make_pair(v1, weight));

	return true;
}

void ListGraph::display() {
	for (int i = 0; i < size; i++) {
		for (std::pair<int, int> v : list[i])
			std::cout << i << ":" << v.first << " - " << v.second<<"   ";
		
		std::cout << std::endl;
	}
}

int ListGraph::kruskalFind(KruskalSet* sets, int vertex) {
	if (sets[vertex].parent != vertex)
		sets[vertex].parent = kruskalFind(sets, sets[vertex].parent);

	return sets[vertex].parent;
}

void ListGraph::kruskalUnion(KruskalSet* sets, int first, int second) {
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

void ListGraph::kruskal() {
	for (int i = 0; i < size; i++) {
		for (std::pair<int, int> v : undirectedGraph[i]) {
			Edge *edge = new Edge;
			edge->source = i;
			edge->target = v.first;
			edge->weight = v.second;

			(*edges).push(*edge);
		}
	}

	KruskalSet* sets = new KruskalSet[size];

	for (int i = 0; i < size; i++) {
		sets[i].parent = i;
		sets[i].rank = 0;
	}

	int i = 0;
	while (i < size - 1) {
		Edge e = (*edges).top();
		(*edges).pop();

		int beginOfSet = kruskalFind(sets, e.source);
		int endOfSet = kruskalFind(sets, e.target);

		if (beginOfSet != endOfSet) {
			(*mst).push_back(e);
			kruskalUnion(sets, beginOfSet, endOfSet);
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

int ListGraph::findEdge(int v1, int v2){
	for (std::pair<int, int> v : list[v1])
		if (v.first == v2) return v.second;	

	return INT_MAX;
}

void ListGraph::dikstra(){
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

	for (int i = 0; i < size; i++) {
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