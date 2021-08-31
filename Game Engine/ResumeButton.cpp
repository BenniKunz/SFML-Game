#include "ResumeButton.h"
#include <iostream>

namespace Engine
{

	ResumeButton::~ResumeButton()
	{
	}

	void ResumeButton::InputHandler()
	{
		Button::InputHandler();
		Button::IsHovered(this->_texture);

		if (Button::IsClicked(this->_texture, _previousClicked, _currentClicked))
		{
			this->_data->stateMachine.RemoveState();
		}
	}

	void ResumeButton::Update(float dt)
	{
		
	}

	void ResumeButton::Draw(float dt)
	{
		Button::Draw(dt);
	}
}


