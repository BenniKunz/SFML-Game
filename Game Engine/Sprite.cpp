#include "Sprite.h"

Engine::Sprite::Sprite(sf::Vector2f position, std::string textureName, GameDataReference data, std::vector<std::shared_ptr<IGamePart>>& gameParts)
	:_position{position}, _data{data}, _textureName{textureName}, _gameParts{gameParts}
{
	_texture.setTexture(this->_data->assets.GetTexture(textureName));
	_texture.setPosition(this->_position.x, this->_position.y);

}

void Engine::Sprite::InputHandler(sf::Event event)
{
}

void Engine::Sprite::Update(float dt, std::vector<std::shared_ptr<IGamePart>>& _gameParts)
{
}

void Engine::Sprite::Draw(float dt)
{
}

void Engine::Sprite::EventHandler(sf::Event event)
{
}

void Engine::Sprite::DealDamage(WeaponType type)
{
}
