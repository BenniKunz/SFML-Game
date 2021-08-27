#include "Graph.h"
#include "Parameters.h"
#include <iostream>
#include "TileType.h"

Graph::Graph(std::array<int, MAP_WIDTH* MAP_HEIGHT> &levelTest)
	:_levelTest{levelTest}
{
}

void Graph::makeGraph()
{
	int x{ 0 };
	int y{ 0 };
	
	for (size_t i = 0; i < MAP_HEIGHT; i++)
	{
		if (i > 0) { y += TILE_HEIGHT; }

		for (size_t j = 0; j < MAP_WIDTH; j++)
		{
			if (j > 0) { x += TILE_WIDTH; }

			TileType type = static_cast<TileType>(_levelTest[i * MAP_WIDTH + j]);
			std::shared_ptr<Node> node = std::make_shared<Node>(x,y,type);
			_allNodes[i][j] = node;
		}
		x = 0;
	}

	for (int i = 0; i < MAP_HEIGHT; i++)
	{

		for (int j = 0; j < MAP_WIDTH; j++)
		{
			
			if (j - 1 >= 0) { _allNodes[i][j]->SetNeighbour(_allNodes[i][j - 1]); }

			if (j + 1 < MAP_WIDTH) { _allNodes[i][j]->SetNeighbour(_allNodes[i][j + 1]); }

			if (i - 1 >= 0) { _allNodes[i][j]->SetNeighbour(_allNodes[i - 1][j]); }

			if (i + 1 < MAP_HEIGHT) { _allNodes[i][j]->SetNeighbour(_allNodes[i + 1][j]); }
		}
	}

}

//std::unordered_map<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>> &Graph::GetNodeEdges()
//{
//	return _edges;
//}



void Graph::printGraph()
{
	for (size_t i = 0; i < MAP_HEIGHT; i++)
	{
		for (size_t j = 0; j < MAP_WIDTH; j++)
		{
			std::cout << "Node Index:" << i << "/" << j 
				<< "Map Position:" << _allNodes[i][j]->GetPosition().x 
				<< "/" << _allNodes[i][j]->GetPosition().y << std::endl;

			for (auto &node : _allNodes[i][j]->GetNeighbour())
			{
				std::cout << "NeighbourNode:"
					<< "Position:" << node->GetPosition().x
					<< "/" << node->GetPosition().y << std::endl;
			}
		}
	}
}
