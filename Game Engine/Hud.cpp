#include "Hud.h"
#include <iostream>
#include "Parameters.h"

namespace Engine
{
	Hud::Hud(GameData& data, std::shared_ptr<Player> player)
		:_data{ data }, _player{ player }
	{
		_numberOfEnemies = 0;
		_enemiesReachedTarget = 0;
		_enemiesDestroyed = 0 ;
		_player->RegisterObserver(this);

		SetTextAttributes(_numberOfEnemiesText, this->_data.assets.GetFont("gameFont"),
			std::to_string(_numberOfEnemies)+ " enemies on the map", sf::Color::White, 15, this->_data.view.getCenter().x + SCREEN_WIDTH / 3, this->_data.view.getCenter().y + SCREEN_HEIGHT / 3);
		SetTextAttributes(_enemiesReachedTargetText , this->_data.assets.GetFont("gameFont"),
			std::to_string(_enemiesReachedTarget) + " enemies reached target", sf::Color::Red, 15, this->_data.view.getCenter().x + SCREEN_WIDTH / 3, this->_data.view.getCenter().y + SCREEN_HEIGHT / 3);
		SetTextAttributes(_activeAmmoText, this->_data.assets.GetFont("gameFont"),
			std::to_string(_player->GetActiveAmmo()), sf::Color::White, 30, this->_data.view.getCenter().x + SCREEN_WIDTH / 3, this->_data.view.getCenter().y + SCREEN_HEIGHT / 3);
		

		_weaponTexture.setTexture(this->_data.assets.GetTexture("gunTexture"));
		_weaponTexture.setPosition(this->_data.view.getCenter().x + SCREEN_WIDTH / 3, this->_data.view.getCenter().y + SCREEN_HEIGHT / 3);

		_hudTable.setTexture(this->_data.assets.GetTexture("hudTable"));
		_hudTable.setScale(2.0f, 2.0f);
		_hudTable.setPosition(this->_data.view.getCenter().x + SCREEN_WIDTH / 3, this->_data.view.getCenter().y + SCREEN_HEIGHT / 3);

		_ammoIcon.setTexture(this->_data.assets.GetTexture("ammoIcon"));
		_ammoIcon.setPosition(this->_data.view.getCenter().x + SCREEN_WIDTH / 3, this->_data.view.getCenter().y + SCREEN_HEIGHT / 3);

		_hp.setTexture(this->_data.assets.GetTexture("hpIcon"));

		_enemyDestruction.setBuffer(this->_data.assets.GetSound("enemyDestruction"));
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
			_weaponTexture.setTexture(this->_data.assets.GetTexture("gunTexture"));
			break;
		case Engine::rocket:
			_weaponTexture.setTexture(this->_data.assets.GetTexture("rocketLauncherTexture"));
			break;
		default:
			break;
		}
	}

	void Hud::OnNotify(GameEvent gameEvent, IGamePart& gamePart)
	{
		switch (gameEvent)
		{
		case enemyReachedTarget:
			_numberOfEnemies--;
			_enemiesReachedTarget++;
			_numberOfEnemiesText.setString(std::to_string(_numberOfEnemies) + " enemies on the map");
			_enemiesReachedTargetText.setString(std::to_string(_enemiesReachedTarget) + " enemies reached target");
			_player->ReduceLives();
			break;
		case enemySpawned:
			_numberOfEnemies++;
			_numberOfEnemiesText.setString(std::to_string(_numberOfEnemies) + " enemies on the map");
			break;

		case enemyDestroyed:
			_numberOfEnemies--;
			_enemiesDestroyed++;
			_enemyDestruction.play();
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

			SetTextAttributes(_itemText, this->_data.assets.GetFont("gameFont"),
				std::to_string(gamePart._value) + " bullets" + " picked up", sf::Color::Black, 60, this->_data.view.getCenter().x, this->_data.view.getCenter().y - 100.0);
			_itemCollected = true;
			break;
		case rocketsCollected:
			_activeAmmoText.setString(std::to_string(_player->GetActiveAmmo()));
			SetTextAttributes(_itemText, this->_data.assets.GetFont("gameFont"),
			std::to_string(gamePart._value) + " rockets" + " picked up", sf::Color::Black, 60, this->_data.view.getCenter().x, this->_data.view.getCenter().y - 100.0);
			
			_itemCollected = true;
			break;

		case healthCollected:
			SetTextAttributes(_itemText, this->_data.assets.GetFont("gameFont"),
				std::to_string(gamePart._value) + " hp" + " picked up", sf::Color::Black, 60, this->_data.view.getCenter().x, this->_data.view.getCenter().y - 100.0);
			_itemCollected = true;
		default:

			break;
		}
	}

	void Hud::Display()
	{

	}

	int Hud::GetNumberOfEnemiesDestroyed()
	{
		return _enemiesDestroyed;
	}

	void Engine::Hud::InputHandler()
	{
	}

	void Engine::Hud::Update(float dt)
	{
		_numberOfEnemiesText.setPosition(this->_data.view.getCenter().x + SCREEN_WIDTH / 3 + 8, this->_data.view.getCenter().y + SCREEN_HEIGHT / 3 + 60);
		_enemiesReachedTargetText.setPosition(this->_data.view.getCenter().x + SCREEN_WIDTH / 3 + 8, this->_data.view.getCenter().y + SCREEN_HEIGHT / 3 + 90);
		_activeAmmoText.setPosition(this->_data.view.getCenter().x + SCREEN_WIDTH / 3 + 37, this->_data.view.getCenter().y + SCREEN_HEIGHT / 3);
		_weaponTexture.setPosition(this->_data.view.getCenter().x + SCREEN_WIDTH / 3 + 65, this->_data.view.getCenter().y + SCREEN_HEIGHT / 3 - 5);
		_ammoIcon.setPosition(this->_data.view.getCenter().x + SCREEN_WIDTH / 3 + 18, this->_data.view.getCenter().y + SCREEN_HEIGHT / 3 + 5);
		_hudTable.setPosition(this->_data.view.getCenter().x + SCREEN_WIDTH / 3, this->_data.view.getCenter().y + SCREEN_HEIGHT / 3);
		
	}

	void Engine::Hud::Draw()
	{
		this->_data.window.draw(_hudTable);
		this->_data.window.draw(_numberOfEnemiesText);
		this->_data.window.draw(_enemiesReachedTargetText);
		this->_data.window.draw(_activeAmmoText);
		this->_data.window.draw(_weaponTexture);
		this->_data.window.draw(_ammoIcon);

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
				_itemText.setPosition(this->_data.view.getCenter().x, this->_data.view.getCenter().y - 100.0);
				this->_data.window.draw(_itemText);
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
			_hp.setPosition(this->_data.view.getCenter().x + SCREEN_WIDTH / 3 + 180 + 20 * i, this->_data.view.getCenter().y + SCREEN_HEIGHT / 3 + 50);

			this->_data.window.draw(_hp);
		}
	}
}

