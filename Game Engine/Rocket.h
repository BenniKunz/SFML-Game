#pragma once
#include "IWeapon.h"
#include <iostream>
#include "Player.h"

namespace Engine
{
    class Rocket :
        public IWeapon
    {
    public:
        Rocket();
        virtual ~Rocket();
        // Inherited via IWeapon
        virtual void Shoot(GameDataReference data, std::vector<std::shared_ptr<IGamePart>>& gameParts, sf::Vector2f position, sf::Vector2f direction, IGamePart* player, int& ammo) override;
    };
}


