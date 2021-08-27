#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "TileType.h"

class Node
{
public:
	Node(int x, int y, TileType type);

	std::vector<std::shared_ptr<Node>> _neighbours;
	
	sf::Vector2i GetPosition();

	TileType& GetTileType();

	void SetNeighbour(std::shared_ptr<Node> node);

	std::vector<std::shared_ptr<Node>>& GetNeighbour();
	

private:
	sf::Vector2i _position;
	TileType _tiletype;

};

