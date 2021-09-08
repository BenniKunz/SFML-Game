#pragma once
#include <SFML/Graphics.hpp>
#include "WeaponType.h"
#include "LayerType.h"

namespace Engine
{
	class IGamePart
	{
	public:

		virtual void InputHandler(float dt) = 0;

		virtual void EventHandler(sf::Event event) = 0;

		virtual void Update(float dt, std::vector<std::shared_ptr<IGamePart>>& _gameParts) = 0;

		virtual void Draw(float dt) = 0;

		virtual sf::FloatRect GetGlobalBounds() = 0;

		virtual void DealDamage(WeaponType type) = 0;

		LayerType _layer{ standard };
		bool _removed{ false };
		int _value{ 0 };

	};
}