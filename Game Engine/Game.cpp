#include "Game.h"
#include "SplashState.h"
#include "Parameters.h"
#include <vld.h>

namespace Engine
{
	Game::Game(int width, int height, std::string title)
	{
		_data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar | sf::Style::Fullscreen);
		
		this->_data->stateMachine.AddState(StateReference(std::make_unique<SplashState>(this->_data)), false);

		_data->view.reset(sf::FloatRect(0.f, 0.f, SCREEN_WIDTH , SCREEN_HEIGHT));
		_data->window.setView(_data->view);

		this->Run();
	}
	void Game::Run()
	{
		float newTime, frameTime, interpolation;

		float currentTime = this->_clock.getElapsedTime().asSeconds();

		while (this->_data->window.isOpen())
		{
			this->_data->stateMachine.ProcessStateChanges();

			newTime = this->_clock.getElapsedTime().asSeconds();

			frameTime = newTime - currentTime;

			currentTime = newTime;

			this->_data->stateMachine.GetActiveState()->InputHandler();		
		
			this->_data->stateMachine.GetActiveState()->Update(frameTime);

			this->_data->stateMachine.GetActiveState()->Draw();
		}

	}
}