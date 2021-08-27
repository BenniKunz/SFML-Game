#include "Enemy.h"
#include <iostream>
#include <cmath>
#include "Parameters.h"

void Engine::Enemy::InputHandler(sf::Event event)
{
}

void Engine::Enemy::Update(float dt, std::vector<std::shared_ptr<IGamePart>>& _gameParts)
{
	_nextPosition = _texture.getPosition() + (_targetPosition - _startPosition) * _speed * dt;

	_texture.setPosition(_nextPosition);

	if (abs(_texture.getPosition().x - _targetPosition.x) <= 0.01f && abs(_texture.getPosition().y - _targetPosition.y) <= 0.01f)
	{
		//_texture.setPosition(_targetPosition);

		_pathIterator++;
		if (_pathIterator != _path.end())
		{
			_targetPosition = sf::Vector2f((*_pathIterator)->GetPosition().x, (*_pathIterator)->GetPosition().y);
			_startPosition = sf::Vector2f((*(_pathIterator - 1))->GetPosition().x, (*(_pathIterator - 1))->GetPosition().y);

		}
	}
	if (_texture.getPosition().x >= SCREEN_WIDTH && !_hasReachedTarget)
	{
		_hasReachedTarget = true;
		this->_removed = true;
		Notify(GameEvent::enemyReachedTarget, *this);
	}
}

void Engine::Enemy::Draw(float dt)
{
	this->_data->window.draw(this->_texture);

}

void Engine::Enemy::DealDamage(WeaponType type)
{
	switch (type)
	{
	case Engine::gun:
		//to do deal damage
		this->_removed = true;
		Notify(GameEvent::enemyDestroyed, *this);
		break;
	case Engine::rocket:
		this->_removed = true;
		Notify(GameEvent::enemyDestroyed, *this);
		break;
	default:
		break;
	}

}

void Engine::Enemy::EventHandler(sf::Event event)
{
}

Engine::Enemy::~Enemy()
{
	std::cout << "enemy destructor" << std::endl;
	_observerList.clear();
}

void Engine::Enemy::RegisterObserver(IObserver* observer)
{
	_observerList.push_back(observer);
}

void Engine::Enemy::RemoveObserver(IObserver* observer)
{
	_observerList.erase(std::remove(_observerList.begin(), _observerList.end(), observer), _observerList.end());
}

void Engine::Enemy::Notify(GameEvent gameEvent, IGamePart& gamePart)
{
	for (auto observer : _observerList)
	{
		observer->OnNotify(gameEvent, gamePart);
	}

}
