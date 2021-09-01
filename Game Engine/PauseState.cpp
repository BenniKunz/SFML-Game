#include "PauseState.h"
#include <sstream>
#include <iostream>
#include "Parameters.h"
#include "MainMenuState.h"
#include "PauseButton.h"
#include "ResumeButton.h"
#include "BackButton.h"

namespace Engine
{
	PauseState::PauseState(GameDataReference data)
		:_data{ data }
	{
		
	}

	PauseState::~PauseState()
	{
		std::cout << "PauseState Destructor" << std::endl;
	}

	void PauseState::Init()
	{
		this->_data->assets.LoadTexture("resumeButton", PAUSE_RESUME_BUTTON);

		_backgroundTexture.setTexture(this->_data->assets.GetTexture("menuBackground"));
		_backgroundTexture.setScale(SCREEN_WIDTH / _backgroundTexture.getGlobalBounds().width, SCREEN_HEIGHT / _backgroundTexture.getGlobalBounds().height);

		std::shared_ptr<ResumeButton> resumeButton = std::make_shared<ResumeButton>(190, 100, _data, "resumeButton");
		std::shared_ptr<BackButton> backButton = std::make_shared<BackButton>(490, 100, _data, "backButton");

		_menuParts.push_back(resumeButton);
		_menuParts.push_back(backButton);
	}

	void PauseState::InputHandler(float dt)
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}
		}

		for (auto& menuPart : _menuParts)
		{
			menuPart->InputHandler();
		}
	}

	void PauseState::Update(float dt)
	{
		_data->view.reset(sf::FloatRect(0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT));
		_data->window.setView(_data->view);

		for (auto& menuPart : _menuParts)
		{
			menuPart->Update(dt);
		}
	}

	void PauseState::Draw(float dt)
	{
		this->_data->window.clear(sf::Color::Red);

		this->_data->window.draw(this->_backgroundTexture);
		
		for (auto& menuPart : _menuParts)
		{
			menuPart->Draw(dt);
		}

		this->_data->window.display();
	}
}

