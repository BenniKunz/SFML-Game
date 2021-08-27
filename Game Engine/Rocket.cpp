#include "Rocket.h"
#include "RocketParticle.h"

namespace Engine
{
	Rocket::Rocket()
	{
		_shootingDelay = 1.5f;
	}
	Rocket::~Rocket()
	{
		std::cout << "Rocket Destructor" << std::endl;
	}
	void Rocket::Shoot(GameDataReference data, std::vector<std::shared_ptr<IGamePart>>& gameParts, sf::Vector2f position, sf::Vector2f direction, IGamePart* player, int& ammo)
	{
		if (ammo <= 0) { return; }
		ammo--;
		std::shared_ptr<RocketParticle> bullet = std::make_shared<RocketParticle>(position, direction, "rocketTexture", data, gameParts, player);
		gameParts.push_back(bullet);
	}
}

