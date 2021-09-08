#pragma once
#include "Sprite.h"
#include "Node.h"
#include <iostream>
#include "ISubject.h"
#include "Hud.h"
#include "TankBullet.h"

namespace Engine
{
	class Enemy
		:public Sprite, public ISubject
	{
	public:
		Enemy(std::vector<std::shared_ptr<Node>>& path, sf::Vector2f position, std::string textureName, GameDataReference data, std::vector<std::shared_ptr<IGamePart>>& gameParts)
			:_path{ path }, _speed{ 60.0f }, _hasReachedTarget{ false }, Sprite(position, textureName, data, gameParts),
			_animation(_textureName, 1, 7, _data, _position), _animationManager(_animation, _data),
			_healthBar(_position, "healthBarRed", _data, _gameParts)
		{
			_pathIterator = _path.begin() + 1;	
			_targetPosition = sf::Vector2f((*(_pathIterator))->GetPosition().x, (*(_pathIterator))->GetPosition().y);
			_startPosition = sf::Vector2f((*(_pathIterator - 1))->GetPosition().x, (*(_pathIterator - 1))->GetPosition().y);

			this->_enemyBody.setTexture(this->_data->assets.GetTexture("enemyBodyDown"));
			this->_enemyBody.setPosition(_position.x + PLAYER_TEXTURE_OFFSET, _position.y + PLAYER_TEXTURE_OFFSET);
			_layer = enemy;
		};

		virtual ~Enemy();

		// Inherited via ISubject
		virtual void RegisterObserver(IObserver* observer) override;
		virtual void RemoveObserver(IObserver* observer) override;
		virtual void Notify(GameEvent gameEvent,  IGamePart& gamePart) override;

	private:
		
		Animation _animation;
		AnimationManager _animationManager;

		sf::Sprite _enemyBody;
		std::vector<IObserver*> _observerList;
		std::vector<std::shared_ptr<Node>>::iterator _pathIterator;
		std::vector<std::shared_ptr<Node>>& _path;
		sf::Vector2f _startPosition;
		sf::Vector2f _nextPosition;
		sf::Vector2f _targetPosition;
		sf::Vector2f _moveDirection;
		HealthBar _healthBar;
		float _hp{ ENEMY_MAX_HP };

		float _speed;
		bool _hasReachedTarget;

		virtual void InputHandler(float dt) override;
		virtual void Update(float dt, std::vector<std::shared_ptr<IGamePart>>& _gameParts) override;
		virtual void Draw(float dt) override;
		virtual void EventHandler(sf::Event event) override;

		void SetEnemyPosition(float dt);
		void SetEnemyTexture();

		virtual sf::FloatRect GetGlobalBounds() override { return this->_enemyBody.getGlobalBounds(); };
		
		void DealDamage(WeaponType type);

	};
}


