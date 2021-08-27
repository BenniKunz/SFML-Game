#include "ControllerStrategy.h"

namespace Engine
{
	ControllerStrategy::ControllerStrategy()
	{
	}

	ControllerStrategy::~ControllerStrategy()
	{
	}

	void ControllerStrategy::SetWeapon(std::unique_ptr<IWeapon> weapon)
	{
		this->_weapon = std::move(weapon);
	}
}

