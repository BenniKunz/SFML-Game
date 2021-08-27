#pragma once
#include "IObserver.h"
#include "GameEvent.h"
#include "IGamePart.h"

namespace Engine
{
	class ISubject
	{
	public:
		void virtual RegisterObserver(IObserver* observer) = 0;

		void virtual RemoveObserver(IObserver* observer) = 0;

		void virtual Notify(GameEvent gameEvent, IGamePart& gamePart) = 0;
	};
}


