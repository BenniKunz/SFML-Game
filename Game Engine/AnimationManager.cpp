#include "AnimationManager.h"
#include <iostream>

namespace Engine
{
	AnimationManager::AnimationManager()
	{
	}
	AnimationManager::AnimationManager(Animation &animation, GameDataReference data)
		:_animation{ animation }, _data {data}, _textureWidth{ (int)_animation._texture.getGlobalBounds().width }, _textureHeight{ (int)_animation._texture.getGlobalBounds().height }
	{
		Update(1.0f / 60.0f);
	}

	void AnimationManager::Update(float dt)
	{
		sf::Time elapsed = _clock.getElapsedTime();

		if (elapsed > sf::seconds(_animation.GetFrameSpeed()))
		{
			elapsed = sf::seconds(0);
			_clock.restart();
			_animation.CurrentColumnPlusOne();

			if (_animation.GetCurrentColumn() >= _animation.GetColumnCount())
			{
				_animation.SetCurrentColumnToZero();
				_animation.CurrentRowPlusOne();
			}

			if (_animation.GetCurrentRow() >= _animation.GetRowCount())
			{
				_animation.SetCurrentRowToZero();
			}

		}

		_animation._texture.setTextureRect(sf::IntRect(0, 0, _textureWidth, _textureHeight));

		_animation._texture.setTextureRect(sf::IntRect(
			_animation.GetFrameWidth() * _animation.GetCurrentColumn(),
			_animation.GetFrameHeight() * _animation.GetCurrentRow(),
			_animation.GetFrameWidth(),
			_animation.GetFrameHeight()));
		
	}

	void AnimationManager::Draw()
	{
		this->_data->window.draw(_animation._texture);
	}
}

