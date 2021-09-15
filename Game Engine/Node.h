#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "TileType.h"
#include <iostream>

class Node
{
public:
	Node(int x, int y, TileType type);
	~Node() { std::cout << "Graph Destructor"; };
	std::vector<std::weak_ptr<Node>> _neighbours;
	
	sf::Vector2i GetPosition();

	TileType& GetTileType();

	void SetNeighbour(std::weak_ptr<Node> node);

	std::vector<std::weak_ptr<Node>>& GetNeighbour();
	

private:
	sf::Vector2i _position;
	TileType _tiletype;

};

