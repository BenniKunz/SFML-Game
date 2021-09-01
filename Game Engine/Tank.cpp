#include "Tank.h"
#include <Eigen/Dense>

Engine::Tank::~Tank()
{

}

void Engine::Tank::InputHandler(float dt)
{

}

void Engine::Tank::Update(float dt, std::vector<std::shared_ptr<IGamePart>>& _gameParts)
{
	/*toPlayer = playerPosition - _position;
	_rotation = (float)Math.Atan2(toPlayer.Y, toPlayer.X);*/

	Eigen::Vector2f tank_facing_n = Eigen::Vector2f(0, 1).normalized();
	Eigen::Vector2f tank_player_n = Eigen::Vector2f(_player->GetPlayerPosition().x - _tankTower.getPosition().x, _player->GetPlayerPosition().y - _tankTower.getPosition().y).normalized();

	float angle = acos((tank_facing_n.dot(tank_player_n)));
	
	angle = angle * (180.0 / PI);
	std::cout << angle << std::endl;

	if (_tankTower.getPosition().x < _player->GetPlayerPosition().x)
	{
		_tankTower.setRotation(-angle);
	}
	else
	{
		_tankTower.setRotation(angle);
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
