#pragma once
#include <SFML/Audio.hpp>

namespace Engine
{
	class State
	{
	public:

		virtual ~State();

		virtual void Init() = 0;

		virtual void InputHandler() = 0;

		virtual void Update(float dt) = 0;

		virtual void Draw(float dt) = 0;
		virtual void Pause() {};
		virtual void Resume() {};

	protected:
		sf::Sound _sound;
		sf::Music _music;
	};

}
