#pragma once
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "StateMachine.h"
#include "AssetManager.h"
#include "InputManager.h"
#include "GameData.h"

namespace Engine
{
	class Game
	{
	public:
		Game(int width, int height, std::string title);
		~Game() { std::cout << "Game Destructor" << std::endl; };

	private:
		sf::Clock _clock;

		GameData _data;

		void Run();

	};
}



