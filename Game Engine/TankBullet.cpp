#include "TankBullet.h"
#include "TankBulletParticle.h"

Engine::TankBullet::TankBullet()
{
	_shootingDelay = 2.5f;
}

Engine::TankBullet::~TankBullet()
{
}

void Engine::TankBullet::Shoot(GameData& data, std::vector<std::shared_ptr<IGamePart>>& gameParts, sf::Vector2f position, sf::Vector2f direction, IGamePart* player, float rotation)
{
	std::shared_ptr<TankBulletParticle> bullet = std::make_shared<TankBulletParticle>(position, direction, "tankBulletTexture", data, gameParts, player, rotation);
	gameParts.push_back(bullet);
}
