#include "House.h"
#include <iostream>

Engine::House::~House()
{
	std::cout << "House Destructor" << std::endl;
}

sf::Vector2f Engine::House::GetHousePosition()
{
	return _position;
}

void Engine::House::InputHandler()
{
}

void Engine::House::EventHandler(sf::Event event)
{
}

void Engine::House::Update(float dt, std::vector<std::shared_ptr<IGamePart>>& _gameParts)
{
	ItemRespawn();
}

void Engine::House::Draw()
{
	this->_data.window.draw(this->_texture);
}

sf::FloatRect Engine::House::GetGlobalBounds()
{
	return _texture.getGlobalBounds();
}

void Engine::House::DealDamage(WeaponType type)
{
	this->_data.window.draw(_texture);
}

void Engine::House::OnNotify(GameEvent gameEvent, IGamePart& gamePart)
{
	if (&gamePart != _bulletItem.get() && &gamePart != _rocketItem.get() && &gamePart != _healthItem.get()) { return; }
		
	switch (gameEvent)
	{
	case rocketsCollected:
		_rocketsCollected = true;
		_rocketsClock.restart();
		break;
	case bulletsCollected:
		_bulletsCollected = true;
		_bulletsClock.restart();
		break;
	case healthCollected:
		_healthCollected = true;
		_healthClock.restart();
		break;
	default:
		break;
	}
}

void Engine::House::Display()
{
}

void Engine::House::ItemRespawn()
{
	if (_rocketsCollected && _rocketsClock.getElapsedTime().asSeconds() >= _itemRespawnTime)
	{
		_rocketItem = std::make_shared<Item>(_player, rocketAmmo, sf::Vector2f{ _position.x + 200, _position.y - 50 }, "ammoTexture", _data, _gameParts, 2);
		_rocketsCollected = false;
		_gameParts.push_back(_rocketItem);
	}
	if (_bulletsCollected && _bulletsClock.getElapsedTime().asSeconds() >= _itemRespawnTime)
	{
		_bulletItem = std::make_shared<Item>(_player, gunAmmo, sf::Vector2f{ _position.x, _position.y - 50 }, "ammoTexture", _data, _gameParts, 5);
		_bulletsCollected = false;
		_gameParts.push_back(_bulletItem);
	}
	if (_healthCollected && _healthClock.getElapsedTime().asSeconds() >= _itemRespawnTime)
	{
		_healthItem = std::make_shared<Item>(_player, health, sf::Vector2f{ _position.x + 100, _position.y - 50 }, "hpTexture", _data, _gameParts, 20);
		_healthCollected = false;
		_gameParts.push_back(_healthItem);
	}
}
