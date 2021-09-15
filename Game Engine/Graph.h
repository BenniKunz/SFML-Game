#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include "Node.h"
#include "Parameters.h"
#include <array>

class Graph
{
public:

	Graph(std::array<int, MAP_WIDTH * MAP_HEIGHT> &levelTest);
	~Graph() { std::cout << "Graph Destructor"; }

	void makeGraph();

	/*std::unordered_map < std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>> &GetNodeEdges();
	std::shared_ptr<Node> GetAllNodes();*/

	void printGraph();

	std::unordered_map < std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>> _edges;
	std::shared_ptr<Node> _allNodes[MAP_HEIGHT][MAP_WIDTH];

private:

	std::array<int, MAP_WIDTH* MAP_HEIGHT>& _levelTest;

	std::vector<std::shared_ptr<Node>> getNeighbours(std::shared_ptr<Node> node)
	{
		return _edges[node];
	}
};

