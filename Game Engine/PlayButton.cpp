#include "PlayButton.h"
#include <iostream>
#include "StateMachine.h"
#include "GameState.h"
#include "MainMenuState.h"

namespace Engine
{

	PlayButton::~PlayButton()
	{
	}

	void PlayButton::InputHandler(sf::Event event)
	{
		Button::InputHandler(event);

		Button::IsHovered(this->_texture);

		if (Button::IsClicked(this->_texture, _previousClicked, _currentClicked))
		{
			this->_data->stateMachine.AddState(StateReference(std::make_unique<GameState>(this->_data)), true);
			
		}
	}

	void PlayButton::Update(float dt)
	{
		
	}

	void PlayButton::Draw(float dt)
	{	
		Button::Draw(dt);
	}
}


