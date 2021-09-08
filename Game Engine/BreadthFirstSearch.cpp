#include "BreadthFirstSearch.h"

namespace Engine
{
	BreadthFirstSearch::BreadthFirstSearch(std::unique_ptr<Graph> graphPtr, std::string textureName)
		:_graph{ std::move(graphPtr) }
	{
		
		
	}

	std::vector<std::shared_ptr<Node>> BreadthFirstSearch::CalculatePath()
	{
		std::shared_ptr<Node> start = _graph->_allNodes[0][0];
		std::shared_ptr<Node> goal = _graph->_allNodes[11][59];
		_frontier.push(start);

		_cameFrom[start] = nullptr;


		while (!_frontier.empty())
		{
			_current = _frontier.front();
			
			_frontier.pop();

			for (auto &node : _current->GetNeighbour())
			{
				if (_cameFrom.find(node) == _cameFrom.end() && node->GetTileType() == TileType::street)
				{
					_frontier.push(node);
					_cameFrom[node] = _current;
				}
			}
		}

		_current = goal;

		while (_current != start)
		{
			_path.push_back(_current);
			_current = _cameFrom[_current];
			
		}
		_path.push_back(start);
		std::reverse(_path.begin(), _path.end());

		return _path;
	}

}


