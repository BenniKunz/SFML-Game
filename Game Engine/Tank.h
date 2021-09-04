#pragma once
#include "Sprite.h"
#include "Player.h"
#include "TankBullet.h"
#include "ControllerStrategy.h"

namespace Engine
{
	class Tank :
		public Sprite, public ControllerStrategy
	{
	public:
		Tank(sf::Vector2f position, std::string textureName, GameDataReference data, std::vector<std::shared_ptr<IGamePart>>& gameParts, std::shared_ptr<Player> player)
			: Sprite(position, textureName, data, gameParts), _player {player}
		{
			_tankTower.setTexture(this->_data->assets.GetTexture("tankTower"));
			_tankTower.setPosition(_position.x + 64, _position.y + 64);
			_tankTower.setOrigin(_tankTower.getGlobalBounds().width / 2, 40);

			this->_weapon = std::make_unique<TankBullet>();
		}

		virtual ~Tank();

		virtual void InputHandler(float dt) override;
		virtual void Update(float dt, std::vector<std::shared_ptr<IGamePart>>& _gameParts) override;
		virtual void Draw(float dt) override;
		virtual void EventHandler(sf::Event event) override;
		virtual void DealDamage(WeaponType type) override;

	private:
		sf::Sprite _tankTower;
		std::shared_ptr<Player> _player;
		float _shootingRangeMax{ 400.0 };
		float _shootingRangeMin{ 50.0 };
		int _ammo{ 100 };
		sf::Clock _clock;
		float _shootingDelay{ 5.0f };
		sf::Vector2f _weaponSpawn;
		sf::Vector2f _weaponDirection;
		// Inherited via ControllerStrategy
		virtual void Display() override;

	};
}
