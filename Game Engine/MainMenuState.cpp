#include "MainMenuState.h"
#include <iostream>
#include "Parameters.h"
#include "Button.h"
#include "PlayButton.h"
#include "SettingsButton.h"

Engine::MainMenuState::MainMenuState(GameDataReference data)
	:_data {data}
{
	_data->view.reset(sf::FloatRect(0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT));
	_data->window.setView(_data->view);
}

Engine::MainMenuState::~MainMenuState()
{
	std::cout << "MainMenu Destructor" << std::endl;
}

void Engine::MainMenuState::Init()
{
	this->_data->assets.LoadTexture("playButton", MAIN_MENU_PLAY_BUTTON);
	this->_data->assets.LoadTexture("settingsButton", MAIN_MENU_SETTINGS_BUTTON);
	
	_backgroundTexture.setTexture(this->_data->assets.GetTexture("menuBackground"));
	_backgroundTexture.setScale(SCREEN_WIDTH / _backgroundTexture.getGlobalBounds().width, SCREEN_HEIGHT / _backgroundTexture.getGlobalBounds().height);


	this->_data->assets.PlayMusic(_music, MAIN_MENU_MUSIC, true);
	

	std::shared_ptr<PlayButton> playButton = std::make_shared<PlayButton>(SCREEN_WIDTH / 2 ,100, _data, "playButton");
	std::shared_ptr<SettingsButton> settingsButton = std::make_shared<SettingsButton>(SCREEN_WIDTH / 2, 350, _data, "settingsButton");

	_menuParts.push_back(playButton);
	_menuParts.push_back(settingsButton);
	
}

void Engine::MainMenuState::InputHandler(float dt)
{
	sf::Event event;

	while (this->_data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			this->_data->window.close();
		}

		if (event.key.code == sf::Keyboard::Escape)
		{
			this->_data->window.close();
		}
	}

	for (auto &menuPart :_menuParts)
	{
		menuPart->InputHandler();
	}
}

void Engine::MainMenuState::Update(float dt)
{
	for (auto &menuPart : _menuParts)
	{
		menuPart->Update(dt);
	}
}

void Engine::MainMenuState::Draw(float dt)
{
	this->_data->window.clear(sf::Color::Red);

	this->_data->window.draw(this->_backgroundTexture);

	for (auto &menuPart : _menuParts)
	{
		menuPart->Draw(dt);
	}

	this->_data->window.display();
}
