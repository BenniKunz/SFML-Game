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
		SplashState(GameData& data);
		virtual ~SplashState();

		// Inherited via State
		virtual void Init() override;
		virtual void InputHandler() override;
		virtual void Update(float dt) override;
		virtual void Draw() override;

	private:
		GameData& _data;

		sf::Clock _clock;

		sf::Sprite _backgroundTexture;
		sf::Sprite _splashLogo;
	};
}



