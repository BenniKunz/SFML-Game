#pragma once
#include "Game.h"
#include "IGamePart.h"
#include "SFML/Graphics.hpp"


namespace Engine
{
	class IWeapon
	{
	public:
		virtual void Shoot(GameDataReference data,
			std::vector<std::shared_ptr<IGamePart>>& gameParts,
			sf::Vector2f position, sf::Vector2f direction,
			IGamePart* player,
			int& ammo) = 0;
			
		virtual ~IWeapon() {};
	};
}