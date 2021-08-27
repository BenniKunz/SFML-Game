#pragma once
#include "SFML/Graphics.hpp"
#include "Game.h"
#include "Button.h"

namespace Engine
{
	class SettingsButton
		: public Button
	{
	public:
		SettingsButton(float x, float y, GameDataReference data, std::string textureName) : Button(x, y, data, textureName)
		{
	
		};
		~SettingsButton();

		// Inherited via IGamePart
		virtual void InputHandler(sf::Event event) override;
		virtual void Update(float dt) override;
		virtual void Draw(float dt) override;
	};

}