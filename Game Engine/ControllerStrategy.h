#pragma once
#include "IWeapon.h"
#include <iostream>

namespace Engine
{
	class ControllerStrategy
	{
	public:
		std::unique_ptr<IWeapon> _weapon;

		ControllerStrategy();
		virtual ~ControllerStrategy();

		virtual void Display() = 0;

		void SetWeapon(std::unique_ptr<IWeapon> weapon);
	};
}



