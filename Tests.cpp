#include "Tests.h"
#include "MatrixGraph.cpp"
#include "ListGraph.cpp"
#include <time.h>
#include <windows.h>
#include <iomanip>

Tests::Tests() {
	this->mG = nullptr;
	this->lG = nullptr;

	for (int i = 0; i < 100; i++)
		init(80, 25, 0);

	std::cout << std::fixed << std::setprecision(2) << mstTimeM / 100.0 << " ";
	std::cout << std::fixed << std::setprecision(2) << pathTimeM / 100.0 << std::endl;

	mstTimeM = 0;
	pathTimeM = 0;
	
	for (int i = 0; i < 100; i++)
		init(80, 50, 0);

	std::cout << std::fixed << std::setprecision(2) << mstTimeM / 100.0 << " ";
	std::cout << std::fixed << std::setprecision(2) << pathTimeM / 100.0 << std::endl;

	mstTimeM = 0;
	pathTimeM = 0;

	for (int i = 0; i < 100; i++)
		init(80, 75, 0);

	std::cout << std::fixed << std::setprecision(2) << mstTimeM / 100.0 << " ";
	std::cout << std::fixed << std::setprecision(2) << pathTimeM / 100.0 << std::endl;

	mstTimeM = 0;
	pathTimeM = 0;

	for (int i = 0; i < 100; i++)
		init(80, 99, 0);

	std::cout << std::fixed << std::setprecision(2) << mstTimeM / 100.0 << " ";
	std::cout << std::fixed << std::setprecision(2) << pathTimeM / 100.0 << std::endl;
	

	system("PAUSE");
}

Tests::~Tests() {
	delete mG;
	delete lG;
}

void Tests::init(int vertices, int density, int startVertex) {
	srand(time(NULL));

	this->mG = new MatrixGraph(vertices, startVertex);
	this->lG = new ListGraph(vertices, startVertex);

	// max. liczba krawedzi to n(n-1)/2, wynik mnoze przez gestosc i zaokraglam w dol.
	int maxEdges = floor((vertices * (vertices - 1) * density / 200));
	int edgesCounter = 0;

	// Dodanie podsatawowoych krawedzi
	for (int i = 0; i < vertices - 1; i++) {
		int weight = (rand() % maxEdges) + 1;

		mG->addEdge(i, i + 1, weight);
		lG->addEdge(i, i + 1, weight);

		edgesCounter++;
	}

	// Dodanie nastepnych krawedzi aby utowrzyly graf o podanje gestosci
	while (edgesCounter < maxEdges) {
		int startVertex = rand() % vertices;
		int endVertex = rand() % vertices;
		int weight = (rand() % maxEdges) + 1;

		// ten sam wierzcholek nie moze byc polaczony z samym soba
		if (startVertex != endVertex) {
			if (mG->findEdge2(startVertex, endVertex) == INT_MAX) {
				mG->addEdge(startVertex, endVertex, weight);
				lG->addEdge(startVertex, endVertex, weight);
				edgesCounter++;
			}
		}
	}

	startTest();
}

long long int Tests::read_QPC(){
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return((long long int)count.QuadPart);
}

void Tests::startTest() {
	long long int frequency, start, elapsed;
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);

	start = read_QPC();
	lG->kruskal();
	elapsed = read_QPC() - start;

	elapsed = (1000000.0 * elapsed) / frequency;

	this->mstTimeM += elapsed;



	start = read_QPC();
	lG->dikstra();
	elapsed = read_QPC() - start;

	elapsed = (1000000.0 * elapsed) / frequency;

	this->pathTimeM += elapsed;

	this->mG = nullptr;
	this->lG = nullptr;
	
}