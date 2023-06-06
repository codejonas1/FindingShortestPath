#pragma once
#include <iostream>
#include <iomanip>
#include <queue>
#include <list>
#include "structures.h"

class MatrixGraph {

public:
	std::priority_queue <Edge, std::vector<Edge>, CompareWeight> *edges;
	std::list<Edge> *mst;
	int** graph;
	int** undirectedGraph;
	int size;
	int startVertex;

	inline MatrixGraph(int size, int startVertex);
	inline ~MatrixGraph();
	inline bool addEdge(int row, int col, int weight);
	inline void display();

	inline int kruskalFind(KruskalSet* sets, int vertex);
	inline void kruskalUnion(KruskalSet* sets, int first, int second);
	inline void kruskal();
	inline int findEdge(int v1, int v2);
	inline int findEdge2(int v1, int v2);
	inline void dikstra();
};

