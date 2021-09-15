#pragma once
#include "State.h"
#include "Game.h"
#include "IMenuPart.h"

namespace Engine
{
	class WinState :
		public State
	{
	public:
		WinState(GameData& data, int level);
		virtual ~WinState();

		// Inherited via State
		virtual void Init() override;
		virtual void InputHandler() override;
		virtual void Update(float dt) override;
		virtual void Draw() override;

	private:
		GameData& _data;
		std::vector<std::shared_ptr<IMenuPart>> _menuParts;
		sf::Sprite _backgroundTexture;
		int _level;
		sf::Text _winningMessage;
		sf::Text _nextLevel;
	};
}




