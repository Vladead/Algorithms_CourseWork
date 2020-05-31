#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "FordFalkerson.h"
#include "List.h"

using namespace std;

int main()
{
	FordFalkerson tempObj;

	ifstream input("input.txt");
	tempObj.buildListOfNodes(input);
	input.close();

	input.open("input.txt");
	tempObj.buildAdjacencyMatrix(input);
	input.close();

	tempObj.printAdjacencyMatrix();

	if (!tempObj.isTransportNet())
	{
		cout << "Unacceptable graph" << endl;
		exit(666);
	}

	int maxFlow = 0;
	maxFlow = tempObj.getMaxFlow();
	cout << "Max flow:" << maxFlow;

	return 0;
}
