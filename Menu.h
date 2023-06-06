#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include "MatrixGraph.h"
#include "ListGraph.h"

class Menu
{
public:
	MatrixGraph* mG;
	ListGraph* lG;
	int choice;

	inline Menu();
	inline ~Menu();

	inline bool file_read_line(std::ifstream& file, int tab[], int size);
	inline void loadFile();
	inline void drawGraph();
	inline void preMenu();
	inline void mainMenu();
};

