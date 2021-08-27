#include "BackButton.h"
#include "StateMachine.h"
#include "GameState.h"
#include "MainMenuState.h"
#include <iostream>

Engine::BackButton::~BackButton()
{
}

void Engine::BackButton::InputHandler(sf::Event event)
{
	Button::InputHandler(event);
	Button::IsHovered(this->_texture);

	if (Button::IsClicked(this->_texture, _previousClicked, _currentClicked))
	{
		this->_data->stateMachine.AddState(StateReference(std::make_unique<MainMenuState>(this->_data)), true);
	}
}

void Engine::BackButton::Update(float dt)
{
	

}

void Engine::BackButton::Draw(float dt)
{
	Button::Draw(dt);
}