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
	this->_data->assets.LoadTexture("bomber", MAIN_MENU_BOMBER);
	_data->assets.LoadFont("gameFont", GAME_FONT);
	
	_backgroundTexture.setTexture(this->_data->assets.GetTexture("menuBackground"));
	_backgroundTexture.setScale(SCREEN_WIDTH / _backgroundTexture.getGlobalBounds().width, SCREEN_HEIGHT / _backgroundTexture.getGlobalBounds().height);
	_bomber.setTexture(this->_data->assets.GetTexture("bomber"));
	_bomber.setPosition(SCREEN_WIDTH / 1.5, -20);
	_bomberTwo.setTexture(this->_data->assets.GetTexture("bomber"));
	_bomberTwo.setPosition(SCREEN_WIDTH / 4, -20);

	this->_data->assets.PlayMusic(_music, MAIN_MENU_MUSIC, true);
	
	std::shared_ptr<PlayButton> playButton = std::make_shared<PlayButton>(SCREEN_WIDTH / 2 ,300, _data, "playButton");
	_menuParts.push_back(playButton);

	_instructions.setFont(*this->_data->assets.GetFont("gameFont"));
	_instructions.setString("Walk up : W\nWalk down: S\nWalk left: A\nWalk right: D\nShoot: L\nWeapon change: P");
	_instructions.setFillColor(sf::Color::White);
	_instructions.setCharacterSize(30);
	_instructions.setPosition(SCREEN_WIDTH / 2 - 100, 400);

	_exitText.setFont(*this->_data->assets.GetFont("gameFont"));
	_exitText.setString("Press 'ESC' to exit");
	_exitText.setFillColor(sf::Color::White);
	_exitText.setCharacterSize(20);
	_exitText.setPosition(SCREEN_WIDTH - 200, 0);
	
}

void Engine::MainMenuState::InputHandler()
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
	_bomber.move(0, 1 * dt * 100);
	_bomberTwo.move(0, 1 * dt * 100);

	for (auto &menuPart : _menuParts)
	{
		menuPart->Update(dt);
	}

	if (_bomber.getPosition().y > SCREEN_HEIGHT)
	{
		_bomber.setPosition(SCREEN_WIDTH / 1.5, -20);
	}
	if (_bomberTwo.getPosition().y > SCREEN_HEIGHT)
	{
		_bomberTwo.setPosition(SCREEN_WIDTH / 4, -20);
	}
}

void Engine::MainMenuState::Draw()
{
	this->_data->window.clear(sf::Color::Red);


	this->_data->window.draw(this->_backgroundTexture);

	for (auto &menuPart : _menuParts)
	{
		menuPart->Draw();
	}

	this->_data->window.draw(_instructions);
	this->_data->window.draw(this->_exitText);
	this->_data->window.draw(this->_bomber);
	this->_data->window.draw(this->_bomberTwo);
	this->_data->window.display();
}
