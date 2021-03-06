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
		ResumeButton(float x, float y, GameData& data, std::string textureName) : Button(x, y, data, textureName)
		{

		};
		~ResumeButton();

		// Inherited via IGamePart
		virtual void InputHandler() override;
		virtual void Update(float dt) override;
		virtual void Draw() override;
		
	};

}
