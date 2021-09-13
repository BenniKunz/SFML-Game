#include "WinState.h"
#include "Parameters.h"
#include "BackButton.h"
#include "NextLevelButton.h"
#include <iostream>

Engine::WinState::WinState(GameDataReference data, int level)
	:_data{ data }, _level {level}
{

}

Engine::WinState::~WinState()
{
	std::cout << "Win Destructor" << std::endl;
}

void Engine::WinState::Init()
{
	this->_data->assets.LoadTexture("retryButton", RETRY_BUTTON);
	_data->assets.LoadTexture("nextLevelButton", NEXT_LEVEL_BUTTON);

	_backgroundTexture.setTexture(this->_data->assets.GetTexture("menuBackground"));
	_backgroundTexture.setScale(SCREEN_WIDTH / _backgroundTexture.getGlobalBounds().width, SCREEN_HEIGHT / _backgroundTexture.getGlobalBounds().height);

	std::shared_ptr<BackButton> backButton = std::make_shared<BackButton>(SCREEN_WIDTH / 2 + 100, 100, _data, "backButton");
	std::shared_ptr<NextLevelButton> levelButton = std::make_shared<NextLevelButton>(SCREEN_WIDTH / 3 + 150, 407, _data, "nextLevelButton", _level);

	_menuParts.push_back(backButton);
	_menuParts.push_back(levelButton);

	_winningMessage.setFont(*this->_data->assets.GetFont("gameFont"));
	_winningMessage.setString("Level " + std::to_string(_level + 1) + " complete!");
	_winningMessage.setFillColor(sf::Color::White);
	_winningMessage.setCharacterSize(60);
	_winningMessage.setPosition(SCREEN_WIDTH/3, 150);

	_nextLevel.setFont(*this->_data->assets.GetFont("gameFont"));
	_nextLevel.setString("next Level");
	_nextLevel.setFillColor(sf::Color::White);
	_nextLevel.setCharacterSize(40);
	_nextLevel.setPosition(SCREEN_WIDTH / 3, 400);

}

void Engine::WinState::InputHandler()
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

void Engine::WinState::Update(float dt)
{
	_data->view.reset(sf::FloatRect(0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT));
	_data->window.setView(_data->view);

	for (auto menuPart : _menuParts)
	{
		menuPart->Update(dt);
	}
}

void Engine::WinState::Draw()
{
	this->_data->window.clear(sf::Color::Red);
	this->_data->window.draw(this->_backgroundTexture);
	this->_data->window.draw(this->_winningMessage);
	this->_data->window.draw(this->_nextLevel);

	for (auto menuPart : _menuParts)
	{
		menuPart->Draw();
	}

	this->_data->window.display();
}

