#include "HealthBar.h"

Engine::HealthBar::~HealthBar()
{
	std::cout << "Healthbar Destructor" << std::endl;
}

void Engine::HealthBar::SetPosition(sf::Vector2f pos)
{
	this->_position = pos;
}

void Engine::HealthBar::InputHandler(float dt)
{
}

void Engine::HealthBar::EventHandler(sf::Event event)
{
}

void Engine::HealthBar::Update(float dt, std::vector<std::shared_ptr<IGamePart>>& _gameParts)
{
	_texture.setPosition(_position);
	_healthBarGreen.setPosition(_position);

}

void Engine::HealthBar::Draw(float dt)
{
	this->_data->window.draw(_texture); //healthBarRed
	this->_data->window.draw(_healthBarGreen);
}

sf::FloatRect Engine::HealthBar::GetGlobalBounds()
{
	return sf::FloatRect();
}

void Engine::HealthBar::DealDamage(WeaponType type)
{
}
