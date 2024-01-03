#pragma once
#include "IGameState.h"

class ExitState : public IGameState
{
public:
	static ExitState* Get();

	void Enter();
	void Exit();

	void HandleEvent(SDL_Event& e);
	void Update();
	void Render();
private:
	static ExitState sExitState;

	ExitState() {};
};

