#include "HealthBar.h"

Engine::HealthBar::~HealthBar()
{
	std::cout << "Healthbar Destructor" << std::endl;
}

void Engine::HealthBar::SetPosition(sf::Vector2f pos)
{
	this->_position = pos;
}

void Engine::HealthBar::MovePosition(sf::Vector2f delta)
{
	_texture.move(delta);
	_healthBarGreen.move(delta);
}

void Engine::HealthBar::ChangeHealthBar(float percentage)
{
	this->_healthBarGreen.setScale(1, 1);
	this->_healthBarGreen.setTextureRect(sf::IntRect(0, 0, this->_healthBarGreenWidth * percentage, this->_healthBarGreen.getGlobalBounds().height));
	this->_healthBarGreen.setScale(0.1, 0.1);
}

void Engine::HealthBar::InputHandler(float dt)
{
}

void Engine::HealthBar::EventHandler(sf::Event event)
{
}

void Engine::HealthBar::Update(float dt, std::vector<std::shared_ptr<IGamePart>>& _gameParts)
{
	_healthBarGreen.setPosition(_position);
	_texture.setPosition(_position);

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
