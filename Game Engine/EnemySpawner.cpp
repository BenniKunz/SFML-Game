#include "EnemySpawner.h"

Engine::EnemySpawner::EnemySpawner(std::vector<std::shared_ptr<Node>>& path, GameData& data, std::vector<std::shared_ptr<IGamePart>>& gameParts, Hud* hud)
	:_path{path}, _data {data}, _gameParts{gameParts}, _hud{hud}
{
}

Engine::EnemySpawner::~EnemySpawner()
{
	std::cout << "EnemySpawner Destructor" << std::endl;
}

void Engine::EnemySpawner::InputHandler()
{
}

void Engine::EnemySpawner::EventHandler(sf::Event event)
{
}

void Engine::EnemySpawner::Update(float dt, std::vector<std::shared_ptr<IGamePart>>& _gameParts)
{
	if (_clock.getElapsedTime().asSeconds() >= 5.0f)
	{
		std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(_path, sf::Vector2f{ 0, 0 }, "enemyWalkDown", _data, _gameParts);
		_count++;
		enemy->RegisterObserver(_hud);
		enemy->Notify(GameEvent::enemySpawned, *enemy);

		_gameParts.push_back(enemy);
		_clock.restart();
	}
}

void Engine::EnemySpawner::Draw()
{

}

sf::FloatRect Engine::EnemySpawner::GetGlobalBounds()
{
	return sf::FloatRect();
}

void Engine::EnemySpawner::DealDamage(WeaponType type)
{
}
