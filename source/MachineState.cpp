#include "MachineState.h"
#include "ExitState.h"
#include "MenuState.h"

MachineState::MachineState()
{
	m_currentState = MenuState::Get();
	m_currentState->Enter();
}

MachineState::~MachineState()
{
	if (m_currentState != nullptr)
	{
		//delete m_currentState;
	}

	if (nextState != nullptr)
	{
		delete nextState;
	}	
}

void MachineState::setNextState(IGameState* newState)
{
	if (nextState != ExitState::Get())
	{
		nextState = newState;
	}
}

void MachineState::HandleEvent(SDL_Event& e)
{
	m_currentState->HandleEvent(e);
}

void MachineState::Update()
{
	m_currentState->Update();
}

void MachineState::changeState()
{
	if (nextState != nullptr)
	{
		m_currentState->Exit();
		nextState->Enter();

		m_currentState = nextState;
		nextState = nullptr;
	}
}

bool MachineState::isRunning() const
{
	return (m_currentState != ExitState::Get());
}
