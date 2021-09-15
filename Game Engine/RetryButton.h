#pragma once
#include "Button.h"

namespace Engine
{
	class RetryButton
		: public Button
	{
	public:
		RetryButton(float x, float y, GameData& data, std::string textureName) : Button(x, y, data, textureName)
		{

		};
		~RetryButton();

		// Inherited via IGamePart
		virtual void InputHandler() override;
		virtual void Update(float dt) override;
		virtual void Draw() override;
	};

}
