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
		SettingsButton(float x, float y, GameData& data, std::string textureName) : Button(x, y, data, textureName)
		{
	
		};
		~SettingsButton();

		// Inherited via IGamePart
		virtual void InputHandler() override;
		virtual void Update(float dt) override;
		virtual void Draw() override;
	};

}