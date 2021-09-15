#include "BackButton.h"
#include "StateMachine.h"
#include "GameState.h"
#include "MainMenuState.h"
#include <iostream>

Engine::BackButton::~BackButton()
{
	std::cout << "BackButton Destructor" << std::endl;
}

void Engine::BackButton::InputHandler()
{
	Button::InputHandler();
	Button::IsHovered(this->_texture);

	if (Button::IsClicked(this->_texture, _previousClicked, _currentClicked))
	{
		this->_data.stateMachine.AddState(StateReference(std::make_shared<MainMenuState>(this->_data)), true);
	}
}

void Engine::BackButton::Update(float dt)
{
	

}

void Engine::BackButton::Draw()
{
	Button::Draw();
}
