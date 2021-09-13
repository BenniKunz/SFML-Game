#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"

namespace Engine
{
	class SplashState
		:public State
	{
	public:
		SplashState(GameDataReference data);
		virtual ~SplashState();

		// Inherited via State
		virtual void Init() override;
		virtual void InputHandler() override;
		virtual void Update(float dt) override;
		virtual void Draw() override;

	private:
		GameDataReference _data;

		sf::Clock _clock;

		sf::Sprite _backgroundTexture;
		sf::Sprite _splashLogo;
	};
}



