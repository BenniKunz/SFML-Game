#pragma once
#include "SFML/Graphics.hpp"
#include "Game.h"
#include "Button.h"

namespace Engine
{
	class PlayButton 
		: public Button
	{
	public:
		PlayButton(float x, float y, GameData& data, std::string textureName) : Button(x, y, data, textureName) 
		{
			
		};
		~PlayButton();

		// Inherited via IGamePart
		virtual void InputHandler() override;
		virtual void Update(float dt) override;
		virtual void Draw() override;
		
	};

}

