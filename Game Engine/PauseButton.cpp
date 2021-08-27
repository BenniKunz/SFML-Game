#include "PauseButton.h"
#include "StateMachine.h"
#include "GameState.h"
#include "PauseState.h"

Engine::PauseButton::~PauseButton()
{
}

void Engine::PauseButton::InputHandler(sf::Event event)
{
	Button::InputHandler(event);
	Button::IsHovered(this->_texture);

	if (Button::IsClicked(this->_texture, _previousClicked, _currentClicked))
	{
		this->_data->stateMachine.AddState(StateReference(std::make_unique<PauseState>(this->_data)), false);
	}
}

void Engine::PauseButton::Update(float dt)
{
	

}

void Engine::PauseButton::Draw(float dt)
{
	Button::Draw(dt);
}
