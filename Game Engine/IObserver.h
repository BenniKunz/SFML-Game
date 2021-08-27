#pragma once
#include "GameEvent.h"
#include "IGamePart.h"

namespace Engine
{
	class IObserver
	{
	public:
		virtual void OnNotify(GameEvent gameEvent, IGamePart &gamePart) = 0;
		virtual void Display() = 0;

	};
}


