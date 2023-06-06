#pragma once
#include "MatrixGraph.h"
#include "ListGraph.h"

class Tests
{
public:
	float mstTimeM = 0;
	float mstTimeL = 0;
	float pathTimeM = 0;
	float pathTimeL = 0;

	MatrixGraph* mG;
	ListGraph* lG;

	inline Tests();
	inline ~Tests();
	inline void init(int vertices, int density, int startVertex);
	inline long long int read_QPC();
	inline void startTest();
};

