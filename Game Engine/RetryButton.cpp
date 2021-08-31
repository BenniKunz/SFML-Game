#include "RetryButton.h"
#include "GameState.h"

Engine::RetryButton::~RetryButton()
{
}

void Engine::RetryButton::InputHandler()
{
	Button::InputHandler();
	Button::IsHovered(this->_texture);

	if (Button::IsClicked(this->_texture, _previousClicked, _currentClicked))
	{
		this->_data->stateMachine.AddState(StateReference(std::make_unique<GameState>(this->_data)), true);
	}
}

void Engine::RetryButton::Update(float dt)
{
}

void Engine::RetryButton::Draw(float dt)
{
	Button::Draw(dt);
}
