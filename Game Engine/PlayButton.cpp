#include "PlayButton.h"
#include <iostream>
#include "StateMachine.h"
#include "GameState.h"
#include "MainMenuState.h"

namespace Engine
{

	PlayButton::~PlayButton()
	{
		std::cout << "PlayButton Destructor" << std::endl;
	}

	void PlayButton::InputHandler()
	{
		Button::InputHandler();

		Button::IsHovered(this->_texture);

		if (Button::IsClicked(this->_texture, _previousClicked, _currentClicked))
		{
			this->_data.stateMachine.AddState(StateReference(std::make_shared<GameState>(this->_data, 0)), true);
			
		}
	}

	void PlayButton::Update(float dt)
	{
		
	}

	void PlayButton::Draw()
	{	
		Button::Draw();
	}
}


