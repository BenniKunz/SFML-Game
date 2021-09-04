#include "RocketParticle.h"

Engine::RocketParticle::~RocketParticle()
{
	std::cout << "RocketParticle Destructor" << std::endl;
}

void Engine::RocketParticle::InputHandler(float dt)
{
}

void Engine::RocketParticle::Update(float dt, std::vector<std::shared_ptr<IGamePart>>& _gameParts)
{
	ParticleMovement(dt);

	CollisionDetection(_gameParts);

	CheckParticleLifeTime();
}

void Engine::RocketParticle::EventHandler(sf::Event event)
{

}

void Engine::RocketParticle::CheckParticleLifeTime()
{
	if (this->_clock.getElapsedTime().asSeconds() > _bulletLifeTime)
	{
		this->_removed = true;
	}
}

void Engine::RocketParticle::ParticleMovement(float dt)
{
	/*this->_position += this->_direction * dt * _speed;
	this->_texture.setPosition(_position.x, _position.y);*/
	_texture.move(this->_direction * dt * _speed); // difference?
}

void Engine::RocketParticle::CollisionDetection(std::vector<std::shared_ptr<Engine::IGamePart>>& _gameParts)
{
	for (auto& gamePart : _gameParts)
	{
		if (gamePart.get() == this || gamePart.get() == _player) { continue; }
		else if (this->_texture.getGlobalBounds().intersects(gamePart->GetGlobalBounds()))
		{
			gamePart->DealDamage(WeaponType::gun);
			this->_removed = true;
		}
	}
}

void Engine::RocketParticle::Draw(float dt)
{
	this->_data->window.draw(this->_texture);
}

void Engine::RocketParticle::SetRocketRotation()
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