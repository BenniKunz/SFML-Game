#pragma once
#include <SFML/Graphics.hpp>

namespace Engine
{
	class InputManager
	{
	public:
		InputManager() {};
		~InputManager() {};

		bool IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window, bool previous, bool current);

		bool IsSpriteHovered(sf::Sprite object, sf::RenderWindow& window);

		sf::Vector2i GetMousePosition(sf::RenderWindow& window);
	};
}


