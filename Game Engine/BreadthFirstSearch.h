#pragma once
#include <queue>
#include "Node.h"
#include "Graph.h"
#include <string>
#include "IGamePart.h"
#include <SFML/Graphics.hpp>
#include "Game.h"

namespace Engine
{
	class BreadthFirstSearch
	{
	public:

		BreadthFirstSearch(std::unique_ptr<Graph> graph, std::string textureFile);
		std::vector<std::shared_ptr<Node>> CalculatePath();

	private:
		std::queue<std::shared_ptr<Node>> _frontier;
		std::unordered_map<std::shared_ptr<Node>, std::shared_ptr<Node>> _cameFrom;
		std::unique_ptr<Graph> _graph;

		std::shared_ptr<Node> _current;
		std::vector<std::shared_ptr<Node>> _path;

		GameDataReference _data;
	};
}



