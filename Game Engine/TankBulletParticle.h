#pragma once
#include "TankBullet.h"
#include "SFML/Graphics.hpp"
#include "IGamePart.h"
#include "Sprite.h"
#include <iostream>


namespace Engine
{
	class TankBulletParticle
		: public Sprite
	{
	public:
		TankBulletParticle(sf::Vector2f position, sf::Vector2f direction, std::string textureName, GameDataReference data, std::vector<std::shared_ptr<IGamePart>>& gameParts, IGamePart* gamePart, float rotation)
			:Sprite(position, textureName, data, gameParts), _direction{ direction }, _gamePart{ gamePart }
		{			
				this->_texture.setOrigin(_texture.getGlobalBounds().width / 2, _texture.getGlobalBounds().height / 2);
				this->_texture.setRotation(rotation);
				_layer = weapon;
		}

		virtual ~TankBulletParticle();

		// Inherited via IGamePart
		virtual void InputHandler() override;

		virtual void Update(float dt, std::vector<std::shared_ptr<IGamePart>>& _gameParts) override;

		virtual void Draw() override;

		virtual void EventHandler(sf::Event event) override;

		virtual sf::FloatRect GetGlobalBounds() override { return this->_texture.getGlobalBounds(); };

	private:
		sf::Vector2f _direction;
		float _speed = 200.0f;
		IGamePart* _gamePart;
		sf::Clock _clock;
		float _bulletLifeTime = 2.0f;

		void CollisionDetection(std::vector<std::shared_ptr<Engine::IGamePart>>& _gameParts);
		void ParticleMovement(float dt);
	};
}



