#pragma once
#include "IGameState.h"
#include "Globals.h"

class MachineState
{
public:
	MachineState();
	~MachineState();

	void setNextState(IGameState* newState);
	void HandleEvent(SDL_Event& e);
	void Update();
	void changeState();

	IGameState* GetState() const { return m_currentState; }
	bool isRunning() const;
private:
};

