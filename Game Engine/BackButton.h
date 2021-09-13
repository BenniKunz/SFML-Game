#pragma once
#include "Button.h"

namespace Engine
{
	class BackButton :
		public Button
	{
	public:
		BackButton(float x, float y, GameDataReference data, std::string textureName) : Button(x, y, data, textureName)
		{

		};
		~BackButton();
		// Inherited via IGamePart
		virtual void InputHandler() override;
		virtual void Update(float dt) override;
		virtual void Draw() override;
	};
}


