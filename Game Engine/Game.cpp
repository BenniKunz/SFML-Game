#include "Game.h"
#include "SplashState.h"
#include "Parameters.h"

namespace Engine
{
	Game::Game(int width, int height, std::string title)
	{
		_data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
		
		this->_data->stateMachine.AddState(StateReference(std::make_unique<SplashState>(this->_data)), false);

		_data->view.reset(sf::FloatRect(0.f, 0.f, SCREEN_WIDTH , SCREEN_HEIGHT));
		_data->window.setView(_data->view);

		this->Run();
	}
	void Game::Run()
	{
		float newTime, frameTime, interpolation;

		float currentTime = this->_clock.getElapsedTime().asSeconds();

		float accumulator = 0.0f;

		while (this->_data->window.isOpen())
		{
			this->_data->stateMachine.ProcessStateChanges();

			newTime = this->_clock.getElapsedTime().asSeconds();

			frameTime = newTime - currentTime;

			if (frameTime > 0.25f)
			{
				frameTime = 0.25f;
			}

			currentTime = newTime;
			accumulator += frameTime;

			while (accumulator >= dt)
			{
				this->_data->stateMachine.GetActiveState()->InputHandler(dt);
				this->_data->stateMachine.GetActiveState()->Update(dt);
				
				accumulator -= dt;
			}

			interpolation = accumulator / dt;

			this->_data->stateMachine.GetActiveState()->Draw(interpolation);
		}

	}
}