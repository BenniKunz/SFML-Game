#include "ItemSpawner.h"


Engine::ItemSpawner::ItemSpawner(std::shared_ptr<Player> player, GameDataReference data, std::vector<std::shared_ptr<IGamePart>>& gameParts)
	:_player {player}, _data {data}, _gameParts {gameParts}
{
}

Engine::ItemSpawner::~ItemSpawner()
{
}

void Engine::ItemSpawner::InputHandler(sf::Event event)
{
}

void Engine::ItemSpawner::EventHandler(sf::Event event)
{
}

void Engine::ItemSpawner::Update(float dt, std::vector<std::shared_ptr<IGamePart>>& gameParts)
{
	if (this->_clock.getElapsedTime().asSeconds() > 10.0f)
	{
		_gameParts.push_back(std::make_shared<Item>(_player, gunAmmo, sf::Vector2f{ 500, 500 }, "ammoTexture", _data, _gameParts, 200));
		_gameParts.push_back(std::make_shared<Item>(_player, health, sf::Vector2f{ 700, 500 }, "hpTexture", _data, _gameParts, 1));

		_clock.restart();
	}
	
}

void Engine::ItemSpawner::Draw(float dt)
{
}

sf::FloatRect Engine::ItemSpawner::GetGlobalBounds()
{
    return sf::FloatRect();
}

void Engine::ItemSpawner::DealDamage(WeaponType type)
{
}
