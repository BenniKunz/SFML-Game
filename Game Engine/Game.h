#pragma once
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "StateMachine.h"
#include "AssetManager.h"
#include "InputManager.h"

namespace Engine
{
	struct GameData
	{
		StateMachine stateMachine;
		sf::RenderWindow window;
		sf::View view;
		AssetManager assets;
		InputManager input;
	};

	typedef std::shared_ptr<GameData> GameDataReference;

	class Game
	{
	public:
		Game(int width, int height, std::string title);

	private:
		const float dt = 1.0f / 60.0f;
		sf::Clock _clock;

		GameDataReference _data = std::make_shared<GameData>();

		void Run();

	};
}



