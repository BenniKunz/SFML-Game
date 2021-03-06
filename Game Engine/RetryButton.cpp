#include "RetryButton.h"
#include "GameState.h"

Engine::RetryButton::~RetryButton()
{
	std::cout << "RetryButton Destructor" << std::endl;
}

void Engine::RetryButton::InputHandler()
{
	Button::InputHandler();
	Button::IsHovered(this->_texture);

	if (Button::IsClicked(this->_texture, _previousClicked, _currentClicked))
	{
		this->_data.stateMachine.AddState(StateReference(std::make_shared<GameState>(this->_data, 0)), true);
	}
}

void Engine::RetryButton::Update(float dt)
{
}

void Engine::RetryButton::Draw()
{
	Button::Draw();
}
