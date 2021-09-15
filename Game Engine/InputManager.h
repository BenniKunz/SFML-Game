#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

namespace Engine
{
	class InputManager
	{
	public:
		InputManager() {};
		~InputManager() { std::cout << "InputManager Destructor" << std::endl; };

		bool IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window, bool previous, bool current);

		bool IsSpriteHovered(sf::Sprite object, sf::RenderWindow& window);

		sf::Vector2i GetMousePosition(sf::RenderWindow& window);
	};
}


