#include "BulletParticle.h"

Engine::BulletParticle::~BulletParticle()
{
	std::cout << "BulletParticle Destructor" << std::endl;
}

void Engine::BulletParticle::InputHandler()
{
}

void Engine::BulletParticle::Update(float dt, std::vector<std::shared_ptr<IGamePart>>& _gameParts)
{
	ParticleMovement(dt);

	CollisionDetection(_gameParts);

	if (this->_clock.getElapsedTime().asSeconds() > _bulletLifeTime)
	{
		this->_removed = true;
	}
}

void Engine::BulletParticle::CollisionDetection(std::vector<std::shared_ptr<Engine::IGamePart>>& _gameParts)
{
	for (auto& gamePart : _gameParts)
	{
		if (gamePart.get() == this || gamePart.get() == _player || gamePart->_layer == weapon) { continue; }
		else
		{
			sf::FloatRect temp = sf::FloatRect(
				gamePart->GetGlobalBounds().left + 20,
				gamePart->GetGlobalBounds().top + 20,
				gamePart->GetGlobalBounds().width - 50,
				gamePart->GetGlobalBounds().height - 50);

			if (this->_texture.getGlobalBounds().intersects(temp))
			{
				gamePart->DealDamage(WeaponType::gun);
				this->_removed = true;
			}	
		}
	}
}

void Engine::BulletParticle::ParticleMovement(float dt)
{
	this->_position += this->_direction * dt * _speed;
	this->_texture.setPosition(_position.x, _position.y);
}

void Engine::BulletParticle::SetBulletRotation()
{
	if (_direction == sf::Vector2f(1, 0))
	{
		this->_texture.setRotation(90.0f);
	}
	else if (_direction == sf::Vector2f(0, 1))
	{
		this->_texture.setRotation(180.0f);
	}
	else if (_direction == sf::Vector2f(-1, 0))
	{
		this->_texture.setRotation(-90.0f);
	}

}

void Engine::BulletParticle::Draw()
{
	this->_data.window.draw(this->_texture);
}

void Engine::BulletParticle::EventHandler(sf::Event event)
{
}


