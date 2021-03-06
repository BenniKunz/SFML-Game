#pragma once
#include "Bullet.h"
#include "SFML/Graphics.hpp"
#include "IGamePart.h"
#include "Sprite.h"
#include <iostream>
#include "Player.h"

namespace Engine
{
	class BulletParticle 
		: public Sprite
	{
	public:
		BulletParticle(sf::Vector2f position, sf::Vector2f direction, std::string textureName, GameData& data, std::vector<std::shared_ptr<IGamePart>>& gameParts, IGamePart *player, float rotation)
			:Sprite(position, textureName, data, gameParts), _direction{direction}, _player{player}
		{		
				this->_texture.setOrigin(_texture.getGlobalBounds().width / 2, _texture.getGlobalBounds().height / 2);
				SetBulletRotation();
				_layer = weapon;
				
				
		}

		virtual ~BulletParticle();

		// Inherited via IGamePart
		virtual void InputHandler() override;

		virtual void Update(float dt, std::vector<std::shared_ptr<IGamePart>>& _gameParts) override;

		virtual void Draw() override;

		virtual void EventHandler(sf::Event event) override;

		virtual sf::FloatRect GetGlobalBounds() override { return this->_texture.getGlobalBounds(); };

	private:
		sf::Vector2f _direction;
		float _speed = 200.0f;
		IGamePart* _player;
		sf::Clock _clock;
		float _bulletLifeTime = 2.0f;
		

		void SetBulletRotation();
		void CollisionDetection(std::vector<std::shared_ptr<Engine::IGamePart>>& _gameParts);
		void ParticleMovement(float dt);
	};
}


