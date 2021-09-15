#include "Bullet.h"
#include "BulletParticle.h"



namespace Engine
{
	Bullet::Bullet()
	{
		_shootingDelay = 0.3f;
	}
	Bullet::~Bullet()
	{
		std::cout << "Bullet Destructor" << std::endl;
	}
	void Bullet::Shoot(GameData& data, std::vector<std::shared_ptr<IGamePart>>& gameParts, sf::Vector2f position, sf::Vector2f direction, IGamePart *player, float rotation)
	{
		std::shared_ptr<BulletParticle> bullet = std::make_shared<BulletParticle>(position, direction, "bulletTexture", data, gameParts, player, rotation);
		gameParts.push_back(bullet);
	}

}
