#include "SplashState.h"
#include <sstream>
#include <iostream>
#include "Parameters.h"
#include "MainMenuState.h"

namespace Engine
{
	SplashState::SplashState(GameDataReference data)
		:_data{data}
	{
	}

	SplashState::~SplashState()
	{
		std::cout << "SplashState destructor" << std::endl;
	}

	void SplashState::Init()
	{
		this->_data->assets.LoadTexture("menuBackground", MENU_BACKGROUND);
		this->_data->assets.LoadTexture("splashLogo", SPLASH_STATE_LOGO);

		_backgroundTexture.setTexture(this->_data->assets.GetTexture("menuBackground"));
		_backgroundTexture.setScale(SCREEN_WIDTH / _backgroundTexture.getGlobalBounds().width, SCREEN_HEIGHT / _backgroundTexture.getGlobalBounds().height);
		
		_splashLogo.setTexture(this->_data->assets.GetTexture("splashLogo"));
		_splashLogo.setPosition(SCREEN_WIDTH / 2 - _splashLogo.getGlobalBounds().width / 2, SCREEN_HEIGHT / 2 - _splashLogo.getGlobalBounds().height / 2);
	
	}

	void SplashState::InputHandler(float dt)
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}
		}

	}

	void SplashState::Update(float dt)
	{
		if (this->_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME)
		{
			this->_data->stateMachine.AddState(StateReference(std::make_unique<MainMenuState>(this->_data)), true);
			this->_data->stateMachine.ProcessStateChanges();
		}

	}

	void SplashState::Draw(float dt)
	{
		this->_data->window.clear(sf::Color::Red);

		this->_data->window.draw(this->_backgroundTexture);
		this->_data->window.draw(this->_splashLogo);
		this->_data->window.display();
	}
}


