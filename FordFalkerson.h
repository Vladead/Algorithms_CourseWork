#pragma once

#include <string>
#include <fstream>
#include <algorithm>
#include <stdexcept>
#include "List.h"

using namespace std;

class FordFalkerson
{
public:
	List<string> listOfNodes;

	int** adjacencyMatrix;

	List<bool> listOfMarks;

public:
	void buildListOfNodes(ifstream& input);

	void buildAdjacencyMatrix(ifstream& input);

	void recursiveSearch(int source, int stock, int** tempMatrix, bool& state);

	int getMaxFlow();

	bool isTransportNet();

	int walkInDepth(int source, int intermediateValue);

	void nullify();

	void makeAllFalse();

	void printAdjacencyMatrix();
};

