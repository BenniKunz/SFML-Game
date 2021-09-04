#pragma once
#pragma once
#include "IWeapon.h"
#include <iostream>

namespace Engine
{
	class TankBullet
		:public IWeapon
	{
	public:
		TankBullet();
		virtual ~TankBullet();
		// Inherited via IWeapon
		virtual void Shoot(GameDataReference data, std::vector<std::shared_ptr<IGamePart>>& gameParts, sf::Vector2f position, sf::Vector2f direction, IGamePart* player, float rotation) override;
	};
}


