#pragma once
#include "Button.h"

namespace Engine
{
	class PauseButton :
		public Button
	{
	public:
		PauseButton(float x, float y, GameDataReference data, std::string textureName) : Button(x, y, data, textureName)
		{

		};
		~PauseButton();
		// Inherited via IGamePart
		virtual void InputHandler() override;
		virtual void Update(float dt) override;
		virtual void Draw() override;
		
	};
}


