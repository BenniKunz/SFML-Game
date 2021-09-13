#include "Item.h"

Engine::Item::~Item()
{
    std::cout << "Item Destructor" << std::endl;
}

void Engine::Item::InputHandler()
{
}

void Engine::Item::EventHandler(sf::Event event)
{
}

void Engine::Item::Update(float dt, std::vector<std::shared_ptr<IGamePart>>& _gameParts)
{

    if (_player->GetGlobalBounds().intersects(this->_texture.getGlobalBounds()))
    {
        _player->CollectItem(_type, _value, this);
        this->_removed = true;
    }
}

void Engine::Item::Draw()
{
    this->_data->window.draw(this->_texture);
}

sf::FloatRect Engine::Item::GetGlobalBounds()
{
    return sf::FloatRect();
}

void Engine::Item::DealDamage(WeaponType type)
{

}
