#pragma once
#include "IMenuPart.h"
#include "SFML/Graphics.hpp"
#include "Game.h"

namespace Engine
{
	class Button
		:public IMenuPart
	{
	public:
		Button(float x, float y, GameDataReference data, std::string textureName);
		~Button();

	protected:

		GameDataReference _data;
		sf::Sprite _texture;
		float _xPosition {};
		float _yPosition {};
		bool _previousClicked;
		bool _currentClicked;

		bool IsClicked(sf::Sprite& texture, bool previous, bool current);

		bool IsHovered(sf::Sprite& texture);

		// Inherited via IGamePart
		virtual void InputHandler(sf::Event event) override;

		virtual void Update(float dt) override;

		virtual void Draw(float dt) override;

	};
}


