#include "Bullet.h"
#include "BulletParticle.h"



namespace Engine
{
	Bullet::Bullet()
	{
		_shootingDelay = 0.8f;
	}
	Bullet::~Bullet()
	{
		std::cout << "Bullet Destructor" << std::endl;
	}
	void Bullet::Shoot(GameDataReference data, std::vector<std::shared_ptr<IGamePart>>& gameParts, sf::Vector2f position, sf::Vector2f direction, IGamePart *player, int& ammo)
	{
		if (ammo <= 0) { return; }
		ammo--;
		std::shared_ptr<BulletParticle> bullet = std::make_shared<BulletParticle>(position, direction, "bulletTexture", data, gameParts, player);
		gameParts.push_back(bullet);
	}

}
