#pragma once

struct Edge {
	int source;
	int weight;
	int target;
};

struct CompareWeight {
	bool operator() (const Edge& e1, const Edge& e2) {
		return e1.weight > e2.weight;
	}
};

struct KruskalSet {
	int parent;
	int rank;
};

struct ListItem {
	int vertex;
	int weight;
};

struct CompareWeight2 {
	bool operator() (const ListItem& e1, const ListItem& e2) {
		return e1.weight > e2.weight;
	}
};