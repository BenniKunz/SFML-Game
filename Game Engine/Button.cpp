#include "Button.h"
#include <iostream>
#include "Parameters.h"

namespace Engine
{
	Button::Button(float x, float y, GameData& data, std::string textureName)
		:_xPosition {x}, _yPosition{y}, _data {data}, _previousClicked{false}, _currentClicked{false}
	{
		_texture.setTexture(this->_data.assets.GetTexture(textureName));
		_texture.setPosition(x - _texture.getGlobalBounds().width / 2 ,y);

	}
	Button::~Button()
	{
		
	}
	bool Button::IsClicked(sf::Sprite& texture, bool previous, bool current)
	{
		if (this->_data.input.IsSpriteClicked(texture, sf::Mouse::Left, this->_data.window, previous, current))
		{
			return true;

		}

		return false;
	}
	bool Button::IsHovered(sf::Sprite& texture)
	{
		if (this->_data.input.IsSpriteHovered(texture, this->_data.window))
		{
			texture.setColor(sf::Color(100, 100, 100));
		}
		else
		{
			texture.setColor(sf::Color::White);
		}
		return false;
	}

	void Button::InputHandler()
	{
		_previousClicked = _currentClicked;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			_currentClicked = true;
		}
		else
		{
			_currentClicked = false;
		}

	}
	void Button::Update(float dt)
	{

	}
	void Button::Draw()
	{
		this->_data.window.draw(this->_texture);
	}
	
}

