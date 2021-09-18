#include "TankBulletParticle.h"

Engine::TankBulletParticle::~TankBulletParticle()
{
	std::cout << "TankBulletParticle Destructor" << std::endl;
}

void Engine::TankBulletParticle::InputHandler()
{
}

void Engine::TankBulletParticle::Update(float dt, std::vector<std::shared_ptr<IGamePart>>& _gameParts)
{

	ParticleMovement(dt);

	CollisionDetection(_gameParts);

	if (this->_clock.getElapsedTime().asSeconds() > _bulletLifeTime)
	{
		this->_removed = true;
	}
}

void Engine::TankBulletParticle::CollisionDetection(std::vector<std::shared_ptr<Engine::IGamePart>>& _gameParts)
{
	for (auto& gamePart : _gameParts)
	{
		if (gamePart->_layer != player) { continue; }
		else
		{
			sf::FloatRect temp = sf::FloatRect(
				gamePart->GetGlobalBounds().left + 20,
				gamePart->GetGlobalBounds().top + 20,
				gamePart->GetGlobalBounds().width - 50,
				gamePart->GetGlobalBounds().height - 50);

			if (this->_texture.getGlobalBounds().intersects(temp))
			{
				gamePart->DealDamage(WeaponType::tankBullet);
				this->_removed = true;
			}
			
		}
	}
}

void Engine::TankBulletParticle::ParticleMovement(float dt)
{
	this->_position += this->_direction * dt * _speed;
	this->_texture.setPosition(_position.x, _position.y);
}



void Engine::TankBulletParticle::Draw()
{
	this->_data.window.draw(this->_texture);
}

void Engine::TankBulletParticle::EventHandler(sf::Event event)
{
}


