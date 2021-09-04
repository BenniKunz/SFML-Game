#pragma once
#include "Sprite.h"
#include <iostream>

namespace Engine
{
	class HealthBar :
		public Sprite
	{
	public:
		HealthBar(sf::Vector2f position, std::string healthBarRed, GameDataReference data, std::vector<std::shared_ptr<IGamePart>>& gameParts)
			:Sprite(position, healthBarRed, data, gameParts)
		{
			_healthBarGreen.setTexture(this->_data->assets.GetTexture("healthBarGreen"));
			_healthBarGreen.setPosition(_position);
			_healthBarGreenWidth = _healthBarGreen.getGlobalBounds().width;
			_texture.setScale(0.1, 0.1);
			_healthBarGreen.setScale(0.1, 0.1);

		}
		
		virtual ~HealthBar();

		void SetPosition(sf::Vector2f pos);

		// Inherited via IGamePart
		virtual void InputHandler(float dt) override;
		virtual void EventHandler(sf::Event event) override;
		virtual void Update(float dt, std::vector<std::shared_ptr<IGamePart>>& _gameParts) override;
		virtual void Draw(float dt) override;
		virtual sf::FloatRect GetGlobalBounds() override;
		virtual void DealDamage(WeaponType type) override;

		sf::Sprite _healthBarGreen;
		float _healthBarGreenWidth;
	};
}


