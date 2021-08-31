#include "GameOverState.h"
#include "Parameters.h"
#include "BackButton.h"
#include "RetryButton.h"

Engine::GameOverState::GameOverState(GameDataReference data)
	:_data{data}
{
	
}

Engine::GameOverState::~GameOverState()
{
}

void Engine::GameOverState::Init()
{
	this->_data->assets.LoadTexture("retryButton", RETRY_BUTTON);

	_backgroundTexture.setTexture(this->_data->assets.GetTexture("mainMenuBackground"));
	_backgroundTexture.setScale(SCREEN_WIDTH / _backgroundTexture.getGlobalBounds().width, SCREEN_HEIGHT / _backgroundTexture.getGlobalBounds().height);

	std::shared_ptr<BackButton> backButton = std::make_shared<BackButton>(490, 100, _data, "backButton");
	std::shared_ptr<RetryButton> retryButton = std::make_shared<RetryButton>(490, 400, _data, "retryButton");

	_menuParts.push_back(backButton);
	_menuParts.push_back(retryButton);

}

void Engine::GameOverState::InputHandler(float dt)
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

void Engine::GameOverState::Update(float dt)
{
	_data->view.reset(sf::FloatRect(0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT));
	_data->window.setView(_data->view);

	for (auto menuPart : _menuParts)
	{
		menuPart->Update(dt);
	}
}

void Engine::GameOverState::Draw(float dt)
{
	this->_data->window.clear(sf::Color::Red);
	this->_data->window.draw(this->_backgroundTexture);

	for (auto menuPart : _menuParts)
	{
		menuPart->Draw(dt);
	}

	this->_data->window.display();
}
