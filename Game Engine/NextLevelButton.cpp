#include "NextLevelButton.h"
#include "GameState.h"

Engine::NextLevelButton::~NextLevelButton()
{
}

void Engine::NextLevelButton::InputHandler()
{
	Button::InputHandler();
	Button::IsHovered(this->_texture);

	if (Button::IsClicked(this->_texture, _previousClicked, _currentClicked))
	{
		this->_data->stateMachine.AddState(StateReference(std::make_shared<GameState>(this->_data, _level + 1)), true);
	}
}

void Engine::NextLevelButton::Update(float dt)
{
}

void Engine::NextLevelButton::Draw()
{
	Button::Draw();
}

