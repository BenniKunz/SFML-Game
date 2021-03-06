#include "ResumeButton.h"
#include <iostream>

namespace Engine
{

	ResumeButton::~ResumeButton()
	{
		std::cout << "ResumeButton Destructor" << std::endl;
	}

	void ResumeButton::InputHandler()
	{
		Button::InputHandler();
		Button::IsHovered(this->_texture);

		if (Button::IsClicked(this->_texture, _previousClicked, _currentClicked))
		{
			this->_data.stateMachine.RemoveState();
		}
	}

	void ResumeButton::Update(float dt)
	{
		
	}

	void ResumeButton::Draw()
	{
		Button::Draw();
	}
}


