#pragma once
#include "State.h"
#include "Game.h"
#include "IMenuPart.h"

namespace Engine
{
	class SettingState :
		public State
	{
	public:
		SettingState(GameData& data);
		virtual ~SettingState();

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
	};
}

