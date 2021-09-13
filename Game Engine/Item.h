#pragma once
#include "Sprite.h"
#include "SFML/Graphics.hpp"
#include "Player.h"

namespace Engine
{
	class Item :
		public Sprite
	{
	public:

		Item(std::shared_ptr<Player> player, ItemType type, sf::Vector2f position, std::string textureName, GameDataReference data, std::vector<std::shared_ptr<IGamePart>>& gameParts, int value)
			: Sprite(position, textureName, data, gameParts), _player {player}, _type {type}
		{
			_value = value;
		}

		virtual ~Item();
	private:
		std::shared_ptr<Player> _player;
		ItemType _type;

		// Inherited via IGamePart
		virtual void InputHandler() override;
		virtual void EventHandler(sf::Event event) override;
		virtual void Update(float dt, std::vector<std::shared_ptr<IGamePart>>& _gameParts) override;
		virtual void Draw() override;
		virtual sf::FloatRect GetGlobalBounds() override;
		virtual void DealDamage(WeaponType type) override;
	};
}


