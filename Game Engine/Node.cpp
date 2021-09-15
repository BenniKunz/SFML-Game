#include "Node.h"

Node::Node(int x, int y, TileType type)
	:_position{x,y}, _tiletype{type}
{

}

sf::Vector2i Node::GetPosition()
{
	return _position;
}

TileType& Node::GetTileType()
{
	return this->_tiletype;
}

void Node::SetNeighbour(std::weak_ptr<Node> node)
{
	_neighbours.push_back(node);
}

std::vector<std::weak_ptr<Node>>& Node::GetNeighbour()
{
	return _neighbours;
}
