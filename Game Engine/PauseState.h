#pragma once
#include "State.h"
#include "Game.h"
#include "SFML/Graphics.hpp"
#include "IMenuPart.h"

namespace Engine
{
	class PauseState
		:public State
	{
	public:
		PauseState(GameData& data);
		virtual ~PauseState();

		// Inherited via State
		virtual void Init() override;
		virtual void InputHandler() override;
		virtual void Update(float dt) override;
		virtual void Draw() override;

	private:
		GameData& _data;
		std::vector<std::shared_ptr<IMenuPart>> _menuParts;
		sf::Sprite _backgroundTexture;
		sf::Sprite _resumeButton;
		sf::Sprite _backButton;
	};



}


