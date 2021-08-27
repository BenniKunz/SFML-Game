#include "SettingState.h"
#include <sstream>
#include <iostream>
#include "Parameters.h"
#include "MainMenuState.h"
#include "ResumeButton.h"

namespace Engine
{
	SettingState::SettingState(GameDataReference data)
		:_data{data}
	{
	}
	SettingState::~SettingState()
	{
		std::cout << "Setting State Destructor" << std::endl;
	}
	void SettingState::Init()
	{
		this->_data->assets.LoadTexture("settingStateBackground", SETTING_MENU_BACKGROUND_FILEPATH);
		this->_data->assets.LoadTexture("resumeButton", SETTING_RESUME_BUTTON);

		_backgroundTexture.setTexture(this->_data->assets.GetTexture("settingStateBackground"));
		_resumeButton.setTexture(this->_data->assets.GetTexture("resumeButton"));

		std::shared_ptr<ResumeButton> resumeButton = std::make_shared<ResumeButton>(190, 100, _data, "resumeButton");

		_menuParts.push_back(resumeButton);
	}

	void SettingState::InputHandler()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}
		}

		for (auto& gamePart : _menuParts)
		{
			gamePart->InputHandler(event);
		}

	}

	void SettingState::Update(float dt)
	{
		for (auto& menuPart : _menuParts)
		{
			menuPart->Update(dt);
		}

	}

	void SettingState::Draw(float dt)
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