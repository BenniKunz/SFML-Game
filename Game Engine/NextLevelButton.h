#pragma once
#include "Button.h"

namespace Engine
{
	class NextLevelButton
		: public Button
	{
	public:
		NextLevelButton(float x, float y, GameDataReference data, std::string textureName, int level) 
			: Button(x, y, data, textureName), _level{level}
		{
			_texture.scale(2.0, 2.0);
		};
		~NextLevelButton();

		// Inherited via IGamePart
		virtual void InputHandler() override;
		virtual void Update(float dt) override;
		virtual void Draw(float dt) override;

	private:
		int _level;
	};

}


