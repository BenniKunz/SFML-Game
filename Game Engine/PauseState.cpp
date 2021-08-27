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
		this->_data->assets.LoadTexture("pauseStateBackground", PAUSE_BACKGROUND_FILEPATH);
		this->_data->assets.LoadTexture("resumeButton", PAUSE_RESUME_BUTTON);

		_backgroundTexture.setTexture(this->_data->assets.GetTexture("pauseStateBackground"));

		std::shared_ptr<ResumeButton> resumeButton = std::make_shared<ResumeButton>(190, 100, _data, "resumeButton");
		std::shared_ptr<BackButton> backButton = std::make_shared<BackButton>(490, 100, _data, "backButton");

		_menuParts.push_back(resumeButton);
		_menuParts.push_back(backButton);
	}

	void PauseState::InputHandler()
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
			menuPart->InputHandler(event);
		}
	}

	void PauseState::Update(float dt)
	{
		
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

