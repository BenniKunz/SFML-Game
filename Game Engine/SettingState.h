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
		SettingState(GameDataReference data);
		virtual ~SettingState();

		// Inherited via State
		virtual void Init() override;
		virtual void InputHandler(float dt) override;
		virtual void Update(float dt) override;
		virtual void Draw(float dt) override;

	private:
		GameDataReference _data;
		std::vector<std::shared_ptr<IMenuPart>> _menuParts;
		sf::Sprite _backgroundTexture;
		sf::Sprite _resumeButton;
	};
}

