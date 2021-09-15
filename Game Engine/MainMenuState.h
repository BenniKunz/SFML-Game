#pragma once
#include "State.h"
#include "Game.h"
#include "SFML/Graphics.hpp"
#include "IMenuPart.h"
#include "PlayButton.h"

namespace Engine
{
	class MainMenuState
		:public State
	{
	public:
		MainMenuState(GameData& data);

		virtual ~MainMenuState();

		// Inherited via State
		virtual void Init() override;
		virtual void InputHandler() override;
		virtual void Update(float dt) override;
		virtual void Draw() override;

	private:
		GameData& _data;;
		std::vector<std::shared_ptr<IMenuPart>> _menuParts;

		sf::Sprite _backgroundTexture;
		sf::Sprite _bomber;
		sf::Sprite _bomberTwo;
		sf::Clock _clock;
		sf::Text _instructions;
		sf::Text _exitText;
		std::shared_ptr<PlayButton> _playButton;
	};
}



