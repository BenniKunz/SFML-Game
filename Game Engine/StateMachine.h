#pragma once
#include <memory>
#include <stack>
#include "State.h"

namespace Engine
{
	typedef std::shared_ptr<State> StateReference;

	class StateMachine
	{
	public:
		StateMachine();
		~StateMachine() {};

		void AddState(StateReference newState, bool isReplacing = true);
		void RemoveState();

		void ProcessStateChanges();

		StateReference& GetActiveState();

	private:

		std::stack<StateReference> _states;
		StateReference _newState;

		bool _isRemoving;
		bool _isAdding;
		bool _isReplacing;

	};
}


