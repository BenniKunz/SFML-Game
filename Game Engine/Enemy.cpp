#include "Enemy.h"
#include <iostream>
#include <cmath>
#include "Parameters.h"

void Engine::Enemy::InputHandler(float dt)
{
}

void Engine::Enemy::Update(float dt, std::vector<std::shared_ptr<IGamePart>>& _gameParts)
{
	
	SetEnemyTexture();
	SetEnemyPosition(dt);

	if (abs(_animationManager._animation._texture.getPosition().x - _targetPosition.x) <= 1.0f && abs(_animationManager._animation._texture.getPosition().y - _targetPosition.y) <= 1.0f)
	{
		//_texture.setPosition(_targetPosition);

		_pathIterator++;
		if (_pathIterator != _path.end())
		{
			_targetPosition = sf::Vector2f((*_pathIterator)->GetPosition().x, (*_pathIterator)->GetPosition().y);
			_startPosition = sf::Vector2f((*(_pathIterator - 1))->GetPosition().x, (*(_pathIterator - 1))->GetPosition().y);

		}
	}
	if (_animationManager._animation._texture.getPosition().x >= (MAP_WIDTH - 2) * TILE_WIDTH && !_hasReachedTarget)
	{
		_hasReachedTarget = true;
		this->_removed = true;
		this->_healthBar._removed = true;
		Notify(GameEvent::enemyReachedTarget, *this);
	}

	this->_animationManager.Update(dt);
	this->_healthBar.Update(dt, _gameParts);
	if (_hp <= 0)
	{
		_removed = true;
		_healthBar._removed = true;
		Notify(GameEvent::enemyDestroyed, *this);
	}
}

void Engine::Enemy::Draw(float dt)
{
	this->_animationManager.Draw(dt);
	this->_data->window.draw(this->_enemyBody);
	this->_healthBar.Draw(dt);
	
}

void Engine::Enemy::SetEnemyPosition(float dt)
{
	if (_targetPosition.x > _startPosition.x)
	{
		_moveDirection = sf::Vector2f(1, 0);
	}
	else if (_targetPosition.x < _startPosition.x)
	{
		_moveDirection = sf::Vector2f(-1, 0);
	}
	else if (_targetPosition.y > _startPosition.y)
	{
		_moveDirection = sf::Vector2f(0, 1);
	}
	else if (_targetPosition.y < _startPosition.y)
	{
		_moveDirection = sf::Vector2f(0, -1);
	}

	_nextPosition = _animationManager._animation._texture.getPosition() + _moveDirection * _speed * dt;
	_animationManager._animation._texture.setPosition(_nextPosition);
	_enemyBody.setPosition(_nextPosition.x + PLAYER_TEXTURE_OFFSET, _nextPosition.y + PLAYER_TEXTURE_OFFSET);
	_healthBar.SetPosition(sf::Vector2f(_animationManager._animation._texture.getPosition().x + 10.0, _animationManager._animation._texture.getPosition().y));
}

void Engine::Enemy::SetEnemyTexture()
{
	if (_targetPosition.x > _startPosition.x)
	{
		this->_enemyBody.setTexture(this->_data->assets.GetTexture("enemyBodyRight"));
		this->_animationManager._animation._texture.setTexture(this->_data->assets.GetTexture("enemyWalkRight"));
	}
	else if (_targetPosition.x < _startPosition.x)
	{
		this->_enemyBody.setTexture(this->_data->assets.GetTexture("enemyBodyLeft"));
		this->_animationManager._animation._texture.setTexture(this->_data->assets.GetTexture("enemyWalkLeft"));
	}
	else if (_targetPosition.y < _startPosition.y)
	{
		this->_enemyBody.setTexture(this->_data->assets.GetTexture("enemyBodyUp"));
		this->_animationManager._animation._texture.setTexture(this->_data->assets.GetTexture("enemyWalkUp"));
	}
	else if (_targetPosition.y > _startPosition.y)
	{
		this->_enemyBody.setTexture(this->_data->assets.GetTexture("enemyBodyDown"));
		this->_animationManager._animation._texture.setTexture(this->_data->assets.GetTexture("enemyWalkDown"));
	}
}


void Engine::Enemy::DealDamage(WeaponType type)
{
	switch (type)
	{
	case Engine::gun:
		_hp -= 50;
		break;
	case Engine::rocket:
		_hp -= 100;
		break;
	default:
		break;
	}
	_hit.play();
	_healthBar.ChangeHealthBar(_hp / ENEMY_MAX_HP);
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
