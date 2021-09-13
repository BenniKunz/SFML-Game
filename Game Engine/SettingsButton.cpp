#include "SettingState.h"
#include "SettingsButton.h"
#include <iostream>

namespace Engine
{

	SettingsButton::~SettingsButton()
	{
	}

	void SettingsButton::InputHandler()
	{
		Button::InputHandler();
		Button::IsHovered(this->_texture);

		if (Button::IsClicked(this->_texture, _previousClicked, _currentClicked))
		{
			this->_data->stateMachine.AddState(StateReference(std::make_shared<SettingState>(this->_data)), false);
		}
	}

	void SettingsButton::Update(float dt)
	{
		
	}

	void SettingsButton::Draw()
	{
		Button::Draw();
	}
}

