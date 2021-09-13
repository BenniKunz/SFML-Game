#include "StateMachine.h"
#include <iostream>

namespace Engine
{
	StateMachine::StateMachine()
		:_isRemoving{ false }, _isAdding{ true }, _isReplacing{false}
	{
		
	}

	void StateMachine::AddState(StateReference newState, bool isReplacing)
	{
		this->_isAdding = true;
		this->_isReplacing = isReplacing;

		this->_newState = newState;

	}

	void StateMachine::RemoveState()
	{
		this->_isRemoving = true;
	}

	void StateMachine::ProcessStateChanges()
	{
		if (this->_isRemoving && !this->_states.empty())
		{
			this->_states.pop();

			if (!this->_states.empty())
			{
				this->_states.top()->Resume();
			}

			this->_isRemoving = false;
		}

		if (this->_isAdding)
		{
			if (!this->_states.empty())
			{
				if (this->_isReplacing)
				{
					while(!_states.empty())
					this->_states.pop();				

				}
				else
				{
					this->_states.top()->Pause();
				}
			}
			this->_states.push(this->_newState);
			this->_states.top()->Init();
			this->_isAdding = false;

		}
	}

	StateReference& StateMachine::GetActiveState()
	{
		return this->_states.top();
	}
}




