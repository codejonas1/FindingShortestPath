#include "Menu.h"
#include "MatrixGraph.cpp"
#include "ListGraph.cpp"
#include <time.h>

Menu::Menu() {
	this->choice = 0;
	this->mG = nullptr;
	this->lG = nullptr;

	preMenu();
}

Menu::~Menu() {
	delete mG;
	delete lG;
}

void Menu::preMenu() {
	if (mG != nullptr || lG != nullptr) {
		this->mG = nullptr;
		this->lG = nullptr;
	}

	do {
		std::cout << "--- MENU ---" << std::endl;
		std::cout << "0. Wyjscie" << std::endl;
		std::cout << "1. Wczytaj graf z pliku" << std::endl;
		std::cout << "2. Wylosuj graf" << std::endl;
		std::cout << "Co chcesz zrobic: ";

		std::cin >> choice;
	} while (choice > 2);

	switch (choice) {
	case 1:
		loadFile();
		break;
	case 2:
		drawGraph();
		break;
	default:
		break;
	}
}

bool Menu::file_read_line(std::ifstream& file, int tab[], int size)
{
	std::string s;
	getline(file, s);

	if (file.fail() || s.empty())
		return(false);

	std::istringstream in_ss(s);

	for (int i = 0; i < size; i++)
	{
		in_ss >> tab[i];
		if (in_ss.fail())
			return(false);
	}
	return(true);
}


void Menu::loadFile() {

	bool isOk = true;
	std::string fileName;
	std::cout << "Podaj nazwe pliku txt (bez rozszerzenia): ";
	std::cin >> fileName;

	fileName += ".txt";

	std::ifstream file;
	int tab[4];
	file.open(fileName.c_str());

	if (file.is_open())
	{
		if (file_read_line(file, tab, 4))
		{
			int graphEdges = tab[0];
			int graphVertices = tab[1];
			int graphStart = tab[2];
			int graphEnd = tab[3];

			mG = new MatrixGraph(graphVertices, graphStart);
			lG = new ListGraph(graphVertices, graphStart);

			for (int i = 0; i < graphEdges; i++) {
				if (file_read_line(file, tab, 3)) {
					mG->addEdge(tab[0], tab[1], tab[2]);
					lG->addEdge(tab[0], tab[1], tab[2]);
				}
				else {
					std::cout << "File error - READ EDGE" << std::endl;
					isOk = false;
					break;
				}
			}

			if (isOk) {
				std::cout << std::endl;
				std::cout << "Graf zostal wczytany poprawnie." << std::endl;
				mainMenu();
			}
		}
		else
			std::cout << "File error - READ INFO" << std::endl;
			
		file.close();
	}
	else 
		std::cout << "File error - OPEN" << std::endl;
	
}


void Menu::drawGraph() {
	srand(time(NULL));

	int vertices, density, startVertex;

	std::cout << "Podaj ilosc wiercholkow: ";
	std::cin >> vertices;

	std::cout << "Podaj wiercholek startowy: ";
	std::cin >> startVertex;

	std::cout << "Podaj gestosc (w %): ";
	std::cin >> density;

	this->mG = new MatrixGraph(vertices, startVertex);
	this->lG = new ListGraph(vertices, startVertex);

	// max. liczba krawedzi to n(n-1)/2, wynik mnoze przez gestosc i zaokraglam w dol.
	int maxEdges = floor((vertices * (vertices - 1) * density / 200));
	int edgesCounter = 0;

	// Dodanie podsatawowoych krawedzi
	for (int i = 0; i < vertices-1; i++) {
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

	mainMenu();

}


void Menu::mainMenu() {
	do
	{
		std::cout << "0. Wczytaj nowy graf" << std::endl;
		std::cout << "1. Wyswietl graf" << std::endl;
		std::cout << "2. Oblicz MST (Kruskal)" << std::endl;
		std::cout << "3. Droga do wierzcholka (Dijkstra)" << std::endl;

		std::cout << "Twoj wybor: ";
		std::cin >> choice;

		std::cout << std::endl;

		switch (choice) {
		case 1:
			std::cout << "Macierz: " << std::endl;
			std::cout << std::endl;

			mG->display();

			std::cout << std::endl;
			std::cout << std::endl;

			std::cout << "Lista: " << std::endl;
			std::cout << std::endl;
			
			lG->display();
			std::cout << std::endl;

			break;
		case 2:
			std::cout << "Macierz: " << std::endl;
			std::cout << std::endl;

			mG->kruskal();

			std::cout << std::endl;
			std::cout << std::endl;

			std::cout << "Lista: " << std::endl;
			std::cout << std::endl;

			lG->kruskal();
			std::cout << std::endl;
			break;
		case 3:
			std::cout << "Macierz: " << std::endl;
			std::cout << std::endl;

			mG->dikstra();

			std::cout << std::endl;
			std::cout << std::endl;

			std::cout << "Lista: " << std::endl;
			std::cout << std::endl;

			lG->dikstra();
			std::cout << std::endl;
			break;
		default:
			break;
		}
		
	} while (choice != 0);

	preMenu();
	
}

