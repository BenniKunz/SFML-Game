#pragma once
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "StateMachine.h"
#include "AssetManager.h"
#include "InputManager.h"

namespace Engine
{
	class GameData
	{
	public:
		StateMachine stateMachine;
		sf::RenderWindow window;
		sf::View view;
		AssetManager assets;
		InputManager input;
	};
}


