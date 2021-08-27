#include "Hud.h"
#include <iostream>
#include "Parameters.h"

namespace Engine
{
	Hud::Hud(GameDataReference data, std::shared_ptr<Player> player)
		:_data{ data }, _player{ player }
	{
		_numberOfEnemies = 0;
		_enemiesReachedTarget = 0;
		_player->RegisterObserver(this);

		SetTextAttributes(_numberOfEnemiesText, this->_data->assets.GetFont("gameFont"),
			std::to_string(_numberOfEnemies), sf::Color::Black, 80, SCREEN_WIDTH - 200, SCREEN_HEIGHT - 200);
		SetTextAttributes(_enemiesReachedTargetText, this->_data->assets.GetFont("gameFont"),
			std::to_string(_enemiesReachedTarget), sf::Color::Red, 80, SCREEN_WIDTH - 400, SCREEN_HEIGHT - 200);
		SetTextAttributes(_activeAmmoText, this->_data->assets.GetFont("gameFont"),
			std::to_string(_player->GetActiveAmmo()), sf::Color::Blue, 80, SCREEN_WIDTH - 600, SCREEN_HEIGHT - 200);
		SetTextAttributes(_playerLives, this->_data->assets.GetFont("gameFont"),
			std::to_string(_player->GetLives()), sf::Color::Green, 80, SCREEN_WIDTH - 50, 50);
	}

	Hud::~Hud()
	{
		std::cout << "Hud destructor called" << std::endl;
	}

	void Hud::SetTextAttributes(sf::Text& text, sf::Font& font, std::string output, sf::Color color, int characterSize, int x, int y)
	{
		text.setFont(font);
		text.setString(output);
		text.setFillColor(color);
		text.setCharacterSize(characterSize);
		text.setPosition(x, y);
	}

	void Hud::OnNotify(GameEvent gameEvent, IGamePart& gamePart)
	{
		switch (gameEvent)
		{
		case GameEvent::enemyReachedTarget:
			_numberOfEnemies--;
			_enemiesReachedTarget++;

			_player->ReduceLives();
			_playerLives.setString(std::to_string(_player->GetLives()));
			break;
		case GameEvent::enemySpawned:
			_numberOfEnemies++;
			break;

		case GameEvent::enemyDestroyed:
			_numberOfEnemies--;
			break;
		case GameEvent::playerShoot:		//switch fall through		
		case weaponSwitch:			
		case bulletsCollected:			
		case rocketsCollected:
			_activeAmmoText.setString(std::to_string(_player->GetActiveAmmo()));
			break;

		case healthCollected:
			_playerLives.setString(std::to_string(_player->GetLives()));
		default:

			break;
		}

	}

	void Hud::Display()
	{

	}

	void Engine::Hud::InputHandler(sf::Event event)
	{
	}

	void Engine::Hud::Update(float dt)
	{
		_numberOfEnemiesText.setString(std::to_string(_numberOfEnemies));
		_enemiesReachedTargetText.setString(std::to_string(_enemiesReachedTarget));
	}

	void Engine::Hud::Draw(float dt)
	{
		this->_data->window.draw(_numberOfEnemiesText);
		this->_data->window.draw(_enemiesReachedTargetText);
		this->_data->window.draw(_activeAmmoText);
		this->_data->window.draw(_playerLives);
	}
}

