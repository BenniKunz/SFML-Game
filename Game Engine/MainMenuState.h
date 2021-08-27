#pragma once
#include "State.h"
#include "Game.h"
#include "SFML/Graphics.hpp"
#include "IMenuPart.h"

namespace Engine
{
	class MainMenuState
		:public State
	{
	public:
		MainMenuState(GameDataReference data);

		virtual ~MainMenuState();

		// Inherited via State
		virtual void Init() override;
		virtual void InputHandler() override;
		virtual void Update(float dt) override;
		virtual void Draw(float dt) override;

	private:
		GameDataReference _data;
		std::vector<std::shared_ptr<IMenuPart>> _menuParts;

		sf::Sprite _backgroundTexture;

		sf::Clock _clock;
	};
}


