#pragma once
#include "IGamePart.h"
#include "SFML/Graphics.hpp"
#include "Game.h"

namespace Engine
{
	class Sprite :
		public IGamePart
	{
	public:
		Sprite(sf::Vector2f position, std::string textureName, GameDataReference data, std::vector<std::shared_ptr<IGamePart>>& gameParts);

		void DealDamage(WeaponType type);
	protected:
		sf::Sprite _texture;
		sf::Vector2f _position;
		std::string _textureName;
		GameDataReference _data;

		std::vector<std::shared_ptr<IGamePart>>& _gameParts;

		// Inherited via IGamePart
		virtual void InputHandler(float dt) override;

		virtual void Update(float dt, std::vector<std::shared_ptr<IGamePart>>& _gameParts) override;

		virtual void Draw(float dt) override;

		virtual void EventHandler(sf::Event event) override;

		virtual sf::FloatRect GetGlobalBounds() override { return this->_texture.getGlobalBounds(); };

	};
}



