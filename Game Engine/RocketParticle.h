#pragma once
#include "Sprite.h"
#include "Player.h"

namespace Engine
{
	class RocketParticle :
		public Sprite
	{
	public:
		RocketParticle(sf::Vector2f position, sf::Vector2f direction, std::string textureName, GameDataReference data, std::vector<std::shared_ptr<IGamePart>>& gameParts, IGamePart* player)
			:Sprite(position, textureName, data, gameParts), _direction{ direction }, _player {player}
		{
			this->_texture.setScale(sf::Vector2f(0.5, 0.5));
		}

		virtual ~RocketParticle();

		// Inherited via IGamePart
		virtual void InputHandler(float dt) override;

		virtual void Update(float dt, std::vector<std::shared_ptr<IGamePart>>& _gameParts) override;

		virtual void EventHandler(sf::Event event) override;

		virtual void Draw(float dt) override;
		
		void CheckParticleLifeTime();

		void ParticleMovement(float dt);

		void CollisionDetection(std::vector<std::shared_ptr<Engine::IGamePart>>& _gameParts);


		virtual sf::FloatRect GetGlobalBounds() override { return this->_texture.getGlobalBounds(); };

	private:
		sf::Vector2f _direction;
		float _speed = 170.0f;
		IGamePart* _player;
		sf::Clock _clock;
		float _bulletLifeTime = 2.0f;

		void SetRocketRotation();
	};
}
