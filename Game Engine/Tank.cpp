#include "Tank.h"
#include <Eigen/Dense>

Engine::Tank::~Tank()
{
	std::cout << "Tank destructor" << std::endl;
}

void Engine::Tank::InputHandler(float dt)
{

}

void Engine::Tank::Update(float dt, std::vector<std::shared_ptr<IGamePart>>& _gameParts)
{
	if (!_broken)
	{
		Eigen::Vector2f tank_facing_n = Eigen::Vector2f(0, 1).normalized();
		Eigen::Vector2f tank_player_n = Eigen::Vector2f(_player->GetPlayerPosition().x - _tankTower.getPosition().x, _player->GetPlayerPosition().y - _tankTower.getPosition().y).normalized();

		float angle = acos((tank_facing_n.dot(tank_player_n)));

		angle = angle * (180.0 / PI);

		TankShooting(angle, sf::Vector2f(tank_player_n.x(), tank_player_n.y()));

	}
	
	if (_hp <= 0)
	{
		_destruction.play();
		_broken = true;
		_texture.setTexture(this->_data->assets.GetTexture("tankBroken"));
		_healthBar->_removed = true;
	}
}

void Engine::Tank::SetTowerRotation(float& angle)
{
	if (_tankTower.getPosition().x < _player->GetPlayerPosition().x)
	{
		angle *= -1;
		_tankTower.setRotation(angle);
	}
	else
	{
		_tankTower.setRotation(angle);
	}
}

void Engine::Tank::Draw(float dt)
{
	this->_data->window.draw(this->_texture);
	if (!_broken)
	{
		this->_data->window.draw(this->_tankTower);
	}
	
}

void Engine::Tank::EventHandler(sf::Event event)
{
}

void Engine::Tank::DealDamage(WeaponType type)
{
	switch (type)
	{
	case Engine::gun:
		_hp -= 5;
		_hit.play();
		break;
	case Engine::rocket:
		_hit.play();
		_hp -= 75;
		break;
	default:
		break;
	}
	
	_healthBar->ChangeHealthBar(_hp / TANK_MAX_HP);
}

void Engine::Tank::TankShooting(float angle, sf::Vector2f tank_player_normalized)
{
	Eigen::Vector2f tank_to_player = Eigen::Vector2f(_player->GetPlayerShootAtPos().x - _tankTower.getPosition().x, _player->GetPlayerShootAtPos().y - _tankTower.getPosition().y);
	float length{ 0.0 };
	length = tank_to_player.norm();
	_weaponSpawn = sf::Vector2f(_tankTower.getPosition().x, _tankTower.getPosition().y) + sf::Vector2f(tank_player_normalized.x * 80.0, tank_player_normalized.y * 80.0);
	_weaponDirection = sf::Vector2f(tank_to_player.normalized().x(), tank_to_player.normalized().y());

	if (length <= _targetingRange)
	{
		SetTowerRotation(angle);
	}

	if (length <= _shootingRangeMax && length >= _shootingRangeMin && _clock.getElapsedTime().asSeconds() > _weapon->_shootingDelay)
	{
		_clock.restart();
		if (_ammo > 0)
		{
			this->_weapon->Shoot(_data, _gameParts, _weaponSpawn, _weaponDirection, this, angle);
			_ammo--;
		}
	}
}

void Engine::Tank::Display()
{
}
