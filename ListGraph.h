#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include "structures.h"

class ListGraph
{
public:
	std::vector<std::vector<std::pair<int, int>>> list;
	std::vector<std::vector<std::pair<int, int>>> undirectedGraph;
	std::priority_queue <Edge, std::vector<Edge>, CompareWeight> *edges;
	std::list<Edge> *mst;
	int size;
	int startVertex;

	inline ListGraph(int size, int startVertex);
	inline ~ListGraph();

	inline bool addEdge(int v1, int v2, int weight);
	inline void display();

	inline int kruskalFind(KruskalSet* sets, int vertex);
	inline void kruskalUnion(KruskalSet* sets, int first, int second);
	inline void kruskal();

	inline int findEdge(int v1, int v2);
	inline void dikstra();

};

