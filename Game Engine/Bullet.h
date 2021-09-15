#pragma once
#include "IWeapon.h"
#include <iostream>

namespace Engine
{
	class Bullet
		:public IWeapon
	{
	public:
		Bullet();
		virtual ~Bullet();
		// Inherited via IWeapon
		virtual void Shoot(GameData& data, std::vector<std::shared_ptr<IGamePart>>& gameParts, sf::Vector2f position, sf::Vector2f direction, IGamePart *player, float rotation) override;
	};
}


