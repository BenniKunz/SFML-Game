#pragma once
#include "Sprite.h"
#include "Node.h"
#include <iostream>
#include "ISubject.h"
#include "Hud.h"

namespace Engine
{
	class Enemy
		:public Sprite, public ISubject
	{
	public:
		Enemy(std::vector<std::shared_ptr<Node>>& path, sf::Vector2f position, std::string textureName, GameDataReference data, std::vector<std::shared_ptr<IGamePart>>& gameParts)
			:_path{ path }, _speed{ 2.0f }, _hasReachedTarget{ false }, Sprite(position, textureName, data, gameParts)
		{
			_pathIterator = _path.begin() + 1;	
			_targetPosition = sf::Vector2f((*(_pathIterator))->GetPosition().x, (*(_pathIterator))->GetPosition().y);
			_startPosition = sf::Vector2f((*(_pathIterator - 1))->GetPosition().x, (*(_pathIterator - 1))->GetPosition().y);
		};

		virtual ~Enemy();

		// Inherited via ISubject
		virtual void RegisterObserver(IObserver* observer) override;
		virtual void RemoveObserver(IObserver* observer) override;
		virtual void Notify(GameEvent gameEvent,  IGamePart& gamePart) override;

	private:
		
		std::vector<IObserver*> _observerList;
		std::vector<std::shared_ptr<Node>>::iterator _pathIterator;
		std::vector<std::shared_ptr<Node>>& _path;
		sf::Vector2f _startPosition;
		sf::Vector2f _nextPosition;
		sf::Vector2f _targetPosition;

		float _speed;
		bool _hasReachedTarget;

		virtual void InputHandler(sf::Event event) override;
		virtual void Update(float dt, std::vector<std::shared_ptr<IGamePart>>& _gameParts) override;
		virtual void Draw(float dt) override;
		virtual void EventHandler(sf::Event event) override;

		virtual sf::FloatRect GetGlobalBounds() override { return this->_texture.getGlobalBounds(); };
		
		void DealDamage(WeaponType type);

		
	};
}


