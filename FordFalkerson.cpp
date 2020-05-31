#pragma once

#include "FordFalkerson.h"

#include <iomanip>

void FordFalkerson::buildListOfNodes(ifstream& input)
{
	char symbol;
	string node;
	int i = 0;
	while (input)
	{
		symbol = input.get();
		if (symbol == ' ')
		{
			i++;
			if (i > 0)
			{
				bool check = true;
				for (size_t i = 0; i < listOfNodes.get_size(); i++)
				{
					if (listOfNodes.get_pointer(i)->data == node)
					{
						check = false;
						break;
					}
				}
				if (check == true)
				{
					listOfNodes.push_back(node);
				}
				node.clear();
			}
			if (i == 2)
			{
				i = 0;
				symbol = input.get();
				while (symbol != '\n')
				{
					if (input.eof())
					{
						return;
					}
					symbol = input.get();
				}
			}
		}
		else
		{
			node.push_back(symbol);
		}
	}

	int nodesCount = 0;
	for (size_t i = 0; i < listOfNodes.get_size(); i++)
	{
		if (listOfNodes.get_pointer(i)->data == "S" || listOfNodes.get_pointer(i)->data == "T")
		{
			nodesCount++;
		}
	}
	if (nodesCount != 2)
	{
		throw invalid_argument("Invalid input");
	}
}

void FordFalkerson::buildAdjacencyMatrix(ifstream& input)
{
	char symbol;
	string firstNode;
	string secondNode;
	string weight;

	for (size_t i = 0; i < listOfNodes.get_size(); i++)	// Count of nodes is known
	{
		listOfMarks.push_back(false);
	}

	adjacencyMatrix = new int* [listOfNodes.get_size()];
	for (size_t i = 0; i < listOfNodes.get_size(); i++)
	{
		adjacencyMatrix[i] = new int[listOfNodes.get_size()];
	}

	int i = 0;
	while (input)
	{
		symbol = input.get();
		if (symbol == ' ')
		{
			i++;
		}
		else
		{
			if (i == 0)
			{
				firstNode.push_back(symbol);
			}
			if (i == 1)
			{
				secondNode.push_back(symbol);
			}
			if (i == 2)
			{
				i = 0;
				while (symbol != '\n')
				{
					weight.push_back(symbol);
					if (input.eof())
					{
						for (size_t i = 0; i < listOfNodes.get_size(); i++)
						{
							if (listOfNodes.get_pointer(i)->data == firstNode)
							{
								for (size_t j = 0; j < listOfNodes.get_size(); j++)
								{
									if (listOfNodes.get_pointer(j)->data == secondNode)
									{
										adjacencyMatrix[i][j] = atoi(weight.c_str());
									}
								}
							}
						}

						return;
					}
					symbol = input.get();
				}
				for (size_t i = 0; i < listOfNodes.get_size(); i++)
				{
					if (listOfNodes.get_pointer(i)->data == firstNode)
					{
						for (size_t j = 0; j < listOfNodes.get_size(); j++)
						{
							if (listOfNodes.get_pointer(j)->data == secondNode)
							{
								adjacencyMatrix[i][j] = atoi(weight.c_str());
							}
						}
					}
				}
				firstNode.clear();
				secondNode.clear();
				weight.clear();
			}
		}
	}
}

void FordFalkerson::recursiveSearch(int source, int stock, int** tempMatrix, bool& state)
{
	int temp = 0;
	for (size_t i = 0; i < listOfNodes.get_size(); i++)
	{
		if (tempMatrix[source][i] != 0)
		{
			switch (tempMatrix[source][i])
			{
			case 1:
				for (size_t j = 0; j < listOfNodes.get_size(); j++)
				{
					if (tempMatrix[j][i] != 0)
					{
						tempMatrix[j][i] = 2;
					}
				}
				break;

			case 2:
				state = false;

				return;

			default:
				break;
			}
			temp++;
			recursiveSearch(i, stock, tempMatrix, state);
		}
	}
	if (temp == 0 && source == stock) {
		state * true;
		for (size_t j = 0; j < listOfNodes.get_size(); j++)
		{
			if (tempMatrix[j][source] != 0)
			{
				tempMatrix[j][source] = 3;
			}
		}

		return;
	}
	else if (temp == 0 && source != stock) {
		state = false;
		for (size_t j = 0; j < listOfNodes.get_size(); j++)
		{
			if (tempMatrix[j][source] != 0)
			{
				tempMatrix[j][source] = 3;
			}
		}

		return;
	}
	else {
		for (size_t j = 0; j < listOfNodes.get_size(); j++)
		{
			if (tempMatrix[j][source] != 0)
			{
				tempMatrix[j][source] = 3;
			}
		}

		return;
	}
}

int FordFalkerson::getMaxFlow()
{
	int intermediateValue = 0;
	int maxFlow = 0;
	int source = 0;
	for (size_t i = 0; i < listOfNodes.get_size(); i++)
	{
		if (listOfNodes.get_pointer(i)->data == "S")
		{
			source = i;
		}
	}

	while (true)
	{
		makeAllFalse();

		intermediateValue = walkInDepth(source, 1000000);
		if (intermediateValue > 0)
		{
			maxFlow += intermediateValue;
		}
		else
		{
			break;
		}
	}

	return maxFlow;
}

bool FordFalkerson::isTransportNet()
{
	int source = -1;
	int stock = -1;
	for (size_t i = 0; i < listOfNodes.get_size(); i++) {
		if (listOfNodes.get_pointer(i)->data == "S")
		{
			source = i;
		}
		if (listOfNodes.get_pointer(i)->data == "T")
		{
			stock = i;
		}
	}
	if (stock == -1 || source == -1)
	{
		throw std::out_of_range("Unacceptable graph");
	}
	int** tempMatrix = new int* [listOfNodes.get_size()];

	for (size_t i = 0; i < listOfNodes.get_size(); i++)
	{
		tempMatrix[i] = new int[listOfNodes.get_size()];
	}

	for (size_t i = 0; i < listOfNodes.get_size(); i++)
	{
		for (size_t j = 0; j < listOfNodes.get_size(); j++)
		{
			if (adjacencyMatrix[i][j] > 0)
			{
				tempMatrix[i][j] = 1;
			}
			else
			{
				tempMatrix[i][j] = 0;
			}
		}
	}
	bool state = true;
	int double_match = -1;
	for (size_t j = 0; j < listOfNodes.get_size(); j++)
	{
		if (tempMatrix[j][source] != static_cast<int>(0))
		{
			tempMatrix[j][source] = static_cast<int>(2);
		}
	}
	recursiveSearch(source, stock, tempMatrix, state);

	return state;
}

int FordFalkerson::walkInDepth(int source, int intermediateValue)
{
	nullify();
	if (listOfMarks.get_pointer(source)->data == true)
	{
		return 0;
	}
	listOfMarks.get_pointer(source)->data = true;
	if (listOfNodes.get_pointer(source)->data == "T")
	{
		return intermediateValue;
	}
	for (size_t i = 0; i < listOfNodes.get_size(); i++)
	{
		if (adjacencyMatrix[source][i] > 0 && listOfMarks.get_pointer(i)->data == false)
		{
			int minIntermediateValue = walkInDepth(i, min(intermediateValue, adjacencyMatrix[source][i]));
			if (minIntermediateValue > 0)
			{
				adjacencyMatrix[source][i] -= minIntermediateValue;
				adjacencyMatrix[i][source] += minIntermediateValue;
				return minIntermediateValue;
			}
		}
	}

	return 0;
}

void FordFalkerson::nullify()
{
	for (int i = 0; i < listOfNodes.get_size(); i++)
	{
		for (int j = 0; j < listOfNodes.get_size(); j++)
		{
			if (adjacencyMatrix[i][j] < 0)
			{
				adjacencyMatrix[i][j] = 0;
			}
		}
	}
}

void FordFalkerson::makeAllFalse()
{
	for (size_t i = 0; i < listOfMarks.get_size(); i++)
	{
		listOfMarks.get_pointer(i)->data = false;
	}
}

void FordFalkerson::printAdjacencyMatrix()
{
	for (size_t i = 0; i < listOfNodes.get_size(); i++)
	{
		cout << setw(5) << listOfNodes.get_pointer(i)->data;
	}
	cout << endl;
	for (size_t i = 0; i < listOfNodes.get_size(); i++)
	{
		for (int j = 0; j < listOfNodes.get_size(); j++)
		{
			if (adjacencyMatrix[i][j] < 0)
			{
				cout << setw(5) << ".";
			}
			else
			{
				cout << setw(5) << adjacencyMatrix[i][j];
			}
		}
		cout << endl;
	}
}
