#include "SettingState.h"
#include <sstream>
#include <iostream>
#include "Parameters.h"
#include "MainMenuState.h"
#include "ResumeButton.h"

namespace Engine
{
	SettingState::SettingState(GameData& data)
		:_data{data}
	{
		_data.view.reset(sf::FloatRect(0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT));
		_data.window.setView(_data.view);
	}
	SettingState::~SettingState()
	{
		std::cout << "Setting State Destructor" << std::endl;
	}
	void SettingState::Init()
	{
		this->_data.assets.LoadTexture("resumeButton", SETTING_RESUME_BUTTON);

		_backgroundTexture.setTexture(this->_data.assets.GetTexture("menuBackground"));
		_backgroundTexture.setScale(SCREEN_WIDTH / _backgroundTexture.getGlobalBounds().width, SCREEN_HEIGHT / _backgroundTexture.getGlobalBounds().height);
		_resumeButton.setTexture(this->_data.assets.GetTexture("resumeButton"));

		std::shared_ptr<ResumeButton> resumeButton = std::make_shared<ResumeButton>(190, 100, _data, "resumeButton");

		_menuParts.push_back(resumeButton);
	}

	void SettingState::InputHandler()
	{
		sf::Event event;

		while (this->_data.window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data.window.close();
			}
		}

		for (auto& menuPart : _menuParts)
		{
			menuPart->InputHandler();
		}

	}

	void SettingState::Update(float dt)
	{
		for (auto& menuPart : _menuParts)
		{
			menuPart->Update(dt);
		}

	}

	void SettingState::Draw()
	{
		this->_data.window.clear(sf::Color::Red);

		this->_data.window.draw(this->_backgroundTexture);

		for (auto& menuPart : _menuParts)
		{
			menuPart->Draw();
		}

		this->_data.window.display();
	}
}