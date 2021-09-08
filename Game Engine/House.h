#pragma once
#include "Sprite.h"
#include "Player.h"
#include "Item.h"

namespace Engine
{
	class House :
		public Sprite, public IObserver
	{
	public:
		House(std::shared_ptr<Player> player, sf::Vector2f position, std::string textureName, GameDataReference data, std::vector<std::shared_ptr<IGamePart>>& gameParts)
			: Sprite(position, textureName, data, gameParts), _player{ player }
		{
			_bulletItem = std::make_shared<Item>(player, gunAmmo, sf::Vector2f{ _position.x, _position.y - 50 }, "ammoTexture", _data, _gameParts, 8);
			_rocketItem = std::make_shared<Item>(player, rocketAmmo, sf::Vector2f{ _position.x + 200, _position.y - 50 }, "ammoTexture", _data, _gameParts, 4);
			_healthItem = std::make_shared<Item>(player, health, sf::Vector2f{ _position.x + 100, _position.y - 50 }, "hpTexture", _data, _gameParts, 10);
			_gameParts.push_back(_bulletItem);
			_gameParts.push_back(_rocketItem);
			_gameParts.push_back(_healthItem);		
			_player->RegisterObserver(this);
		}

		virtual ~House();

		sf::Vector2f GetHousePosition();

		virtual void InputHandler(float dt) override;
		virtual void EventHandler(sf::Event event) override;
		virtual void Update(float dt, std::vector<std::shared_ptr<IGamePart>>& _gameParts) override;
		virtual void Draw(float dt) override;
		virtual sf::FloatRect GetGlobalBounds() override;
		virtual void DealDamage(WeaponType type) override;


		// Inherited via IObserver
		virtual void OnNotify(GameEvent gameEvent, IGamePart& gamePart) override;

		virtual void Display() override;
	private:
		std::shared_ptr<Player> _player;
		std::shared_ptr<Item> _bulletItem;
		std::shared_ptr<Item> _rocketItem;
		std::shared_ptr<Item> _healthItem;
		sf::Clock _rocketsClock;
		sf::Clock _bulletsClock;
		sf::Clock _healthClock;
		bool _rocketsCollected{ false };
		bool _bulletsCollected{ false };
		bool _healthCollected{ false };

		void ItemRespawn();
	};
}


