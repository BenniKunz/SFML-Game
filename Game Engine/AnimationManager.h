#pragma once
#include "Animation.h"
#include "Game.h"

namespace Engine
{
	class AnimationManager
	{
	public:
		AnimationManager();
		AnimationManager(Animation &animation, GameDataReference data);

		void Update(float dt);

		void Draw();
		Animation _animation;

	private:
		sf::Clock _clock;
		GameDataReference _data;
		int _textureWidth;
		int _textureHeight;

	};
}


