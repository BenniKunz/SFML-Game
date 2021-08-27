#pragma once
#include "SFML/Graphics.hpp"
#include "Game.h"
#include "Button.h"

namespace Engine
{
	class ResumeButton
		: public Button
	{
	public:
		ResumeButton(float x, float y, GameDataReference data, std::string textureName) : Button(x, y, data, textureName)
		{

		};
		~ResumeButton();

		// Inherited via IGamePart
		virtual void InputHandler(sf::Event event) override;
		virtual void Update(float dt) override;
		virtual void Draw(float dt) override;
		
	};

}
