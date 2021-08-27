#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"


namespace Engine
{
	class Animation
	{
	public:

		Animation();
		Animation(std::string textureName, int rowCount, int columnCount, GameDataReference data, sf::Vector2f position);

		int GetFrameHeight();
		int GetFrameWidth();
		float GetFrameSpeed();

		int GetCurrentColumn();
		int GetCurrentRow();

		void CurrentColumnPlusOne();
		void SetCurrentColumnToZero();
		void CurrentRowPlusOne();
		void SetCurrentRowToZero();

		int GetColumnCount();
		int GetRowCount();

		sf::Sprite _texture;
		std::string _textureName;
		GameDataReference _data;

	private:

		int _currentColumn{ 0 };
		int _currentRow{ 0 };
		int _rowCount;
		int _columnCount;
		float _frameSpeed;
		sf::Vector2f _position;
	};

}

