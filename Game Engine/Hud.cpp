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
			std::to_string(_numberOfEnemies), sf::Color::Black, 80, SCREEN_WIDTH - 200, SCREEN_HEIGHT - 600);
		SetTextAttributes(_enemiesReachedTargetText, this->_data->assets.GetFont("gameFont"),
			std::to_string(_enemiesReachedTarget), sf::Color::Red, 80, SCREEN_WIDTH - 400, SCREEN_HEIGHT - 600);
		SetTextAttributes(_activeAmmoText, this->_data->assets.GetFont("gameFont"),
			std::to_string(_player->GetActiveAmmo()), sf::Color::White, 30, this->_data->view.getCenter().x + SCREEN_WIDTH / 3, this->_data->view.getCenter().y + SCREEN_HEIGHT / 3);
		

		_weaponTexture.setTexture(this->_data->assets.GetTexture("gunTexture"));
		_weaponTexture.setPosition(this->_data->view.getCenter().x + SCREEN_WIDTH / 3, this->_data->view.getCenter().y + SCREEN_HEIGHT / 3);

		_hudTable.setTexture(this->_data->assets.GetTexture("hudTable"));
		_hudTable.setScale(2.0f, 2.0f);
		_hudTable.setPosition(this->_data->view.getCenter().x + SCREEN_WIDTH / 3, this->_data->view.getCenter().y + SCREEN_HEIGHT / 3);

		_ammoIcon.setTexture(this->_data->assets.GetTexture("ammoIcon"));
		_ammoIcon.setPosition(this->_data->view.getCenter().x + SCREEN_WIDTH / 3, this->_data->view.getCenter().y + SCREEN_HEIGHT / 3);

		_hp.setTexture(this->_data->assets.GetTexture("hpIcon"));
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

	void Hud::ChangeWeaponTexture()
	{
		WeaponType type = _player->GetActiveWeapon();
		switch (type)
		{
		case Engine::gun:
			_weaponTexture.setTexture(this->_data->assets.GetTexture("gunTexture"));
			break;
		case Engine::rocket:
			_weaponTexture.setTexture(this->_data->assets.GetTexture("rocketLauncherTexture"));
			break;
		default:
			break;
		}
	}

	void Hud::OnNotify(GameEvent gameEvent, IGamePart& gamePart)
	{
		std::string text = " " + gamePart._name;
		switch (gameEvent)
		{
		case enemyReachedTarget:
			_numberOfEnemies--;
			_enemiesReachedTarget++;

			_player->ReduceLives();
			break;
		case enemySpawned:
			_numberOfEnemies++;
			break;

		case enemyDestroyed:
			_numberOfEnemies--;
			break;
		case playerShoot:
			_activeAmmoText.setString(std::to_string(_player->GetActiveAmmo()));
			break;
		case weaponSwitch:
			_activeAmmoText.setString(std::to_string(_player->GetActiveAmmo()));
			ChangeWeaponTexture();
			break;
		case bulletsCollected:
			_activeAmmoText.setString(std::to_string(_player->GetActiveAmmo()));

			SetTextAttributes(_itemText, this->_data->assets.GetFont("gameFont"),
				std::to_string(gamePart._value) + text + " picked up", sf::Color::Black, 40, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 5);
			_itemCollected = true;
			break;
		case rocketsCollected:
			_activeAmmoText.setString(std::to_string(_player->GetActiveAmmo()));
			SetTextAttributes(_itemText, this->_data->assets.GetFont("gameFont"),
			std::to_string(gamePart._value) + text + " picked up", sf::Color::Black, 60, this->_data->view.getCenter().x, this->_data->view.getCenter().y - 100.0);
			
			_itemCollected = true;
			break;

		case healthCollected:
			SetTextAttributes(_itemText, this->_data->assets.GetFont("gameFont"),
				std::to_string(gamePart._value) + text + " picked up", sf::Color::Black, 60, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 5);
			_itemCollected = true;
		default:

			break;
		}
	}

	void Hud::Display()
	{

	}

	void Engine::Hud::InputHandler()
	{
	}

	void Engine::Hud::Update(float dt)
	{
		_activeAmmoText.setPosition(this->_data->view.getCenter().x + SCREEN_WIDTH / 3 + 37, this->_data->view.getCenter().y + SCREEN_HEIGHT / 3);
		_weaponTexture.setPosition(this->_data->view.getCenter().x + SCREEN_WIDTH / 3 + 65, this->_data->view.getCenter().y + SCREEN_HEIGHT / 3 - 5);
		_ammoIcon.setPosition(this->_data->view.getCenter().x + SCREEN_WIDTH / 3 + 18, this->_data->view.getCenter().y + SCREEN_HEIGHT / 3 + 5);

		_hudTable.setPosition(this->_data->view.getCenter().x + SCREEN_WIDTH / 3, this->_data->view.getCenter().y + SCREEN_HEIGHT / 3);
		_numberOfEnemiesText.setString(std::to_string(_numberOfEnemies));
		_enemiesReachedTargetText.setString(std::to_string(_enemiesReachedTarget));
	}

	void Engine::Hud::Draw(float dt)
	{
		this->_data->window.draw(_hudTable);
		this->_data->window.draw(_numberOfEnemiesText);
		this->_data->window.draw(_enemiesReachedTargetText);
		this->_data->window.draw(_activeAmmoText);
		this->_data->window.draw(_weaponTexture);
		this->_data->window.draw(_ammoIcon);

		DrawHP();
		DrawItemCollectedFeedback();
	}
	void Engine::Hud::DrawItemCollectedFeedback()
	{
		if (_itemCollected)
		{
			if (_clockStarted == false)
			{
				_clock.restart();
				_clockStarted = true;
			}
			_elapsed = _clock.getElapsedTime();

			if (_elapsed.asSeconds() <= 2.0f)
			{
				_itemText.setPosition(this->_data->view.getCenter().x, this->_data->view.getCenter().y - 100.0);
				this->_data->window.draw(_itemText);
			}
			else
			{
				_clockStarted = false;
				_itemCollected = false;
				_elapsed.Zero;
			}

		}
	}
	void Hud::DrawHP()
	{
		for (int i = 0; i < _player->GetLives(); i++)
		{
			_hp.setPosition(this->_data->view.getCenter().x + SCREEN_WIDTH / 3 + 180 + 20 * i, this->_data->view.getCenter().y + SCREEN_HEIGHT / 3 + 50);

			this->_data->window.draw(_hp);
		}
	}
}

