#pragma once
#include "IGamePart.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include "Item.h"

namespace Engine
{
	class ItemSpawner :
		public IGamePart
	{
	public:
		ItemSpawner(std::shared_ptr<Player> player, GameDataReference data, std::vector<std::shared_ptr<IGamePart>>& gameParts);

		virtual ~ItemSpawner();

		// Inherited via IGamePart
		virtual void InputHandler(float dt) override;

		virtual void EventHandler(sf::Event event) override;

		virtual void Update(float dt, std::vector<std::shared_ptr<IGamePart>>& _gameParts) override;

		virtual void Draw(float dt) override;

		virtual sf::FloatRect GetGlobalBounds() override;

		virtual void DealDamage(WeaponType type) override;

	private:
		sf::Clock _clock;
		std::shared_ptr<Player> _player;
		GameDataReference _data;
		std::vector<std::shared_ptr<IGamePart>>& _gameParts;
	};
}


