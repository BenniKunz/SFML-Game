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
	/*toPlayer = playerPosition - _position;
	_rotation = (float)Math.Atan2(toPlayer.Y, toPlayer.X);*/
	//float _rotation{ 0.0 };
	
	Eigen::Vector2f tank_facing_n = Eigen::Vector2f(0, 1).normalized();
	Eigen::Vector2f tank_player_n = Eigen::Vector2f(_player->GetPlayerPosition().x - _tankTower.getPosition().x, _player->GetPlayerPosition().y - _tankTower.getPosition().y).normalized();

	//_rotation = atan2f(tank_player_n.x(), tank_player_n.y());
	float angle = acos((tank_facing_n.dot(tank_player_n)));
	
	//_rotation = _rotation * (180.0 / PI);
	angle = angle * (180.0 / PI);

	/*_tankTower.setRotation(angle);*/
	if (_tankTower.getPosition().x < _player->GetPlayerPosition().x)
	{
		angle *= -1;
		_tankTower.setRotation(angle);
		/*_weaponSpawn.x = cos(angle * _weaponSpawn.x) - sin(angle * _weaponSpawn.y);
		_weaponSpawn.y = sin(angle * _weaponSpawn.x) + cos(angle * _weaponSpawn.y);*/
	}
	else
	{
		_tankTower.setRotation(angle);
	}
	
	Eigen::Vector2f tank_to_player = Eigen::Vector2f(_player->GetPlayerPosition().x - _tankTower.getPosition().x, _player->GetPlayerPosition().y - _tankTower.getPosition().y);
	float length{ 0.0 };
	length = tank_to_player.norm();
	_weaponSpawn = sf::Vector2f(_tankTower.getPosition().x, _tankTower.getPosition().y) + sf::Vector2f(tank_player_n.x() * 80.0, tank_player_n.y() * 80.0);
	_weaponDirection = sf::Vector2f(tank_to_player.normalized().x(), tank_to_player.normalized().y());

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

void Engine::Tank::Draw(float dt)
{
	this->_data->window.draw(this->_texture);
	this->_data->window.draw(this->_tankTower);
}

void Engine::Tank::EventHandler(sf::Event event)
{
}

void Engine::Tank::DealDamage(WeaponType type)
{
}

void Engine::Tank::Display()
{
}
