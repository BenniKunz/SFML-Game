#pragma once
#include <SFML/Graphics.hpp>

namespace Engine
{
	class IMenuPart
	{
	public:

		virtual void InputHandler() = 0;

		virtual void Update(float dt) = 0;

		virtual void Draw(float dt) = 0;
	};
}