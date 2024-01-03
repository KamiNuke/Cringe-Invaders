#pragma once
#include "SDL.h"

class IGameState
{
public:
	virtual void Enter() = 0;
	virtual void Exit() = 0;

	virtual void HandleEvent(SDL_Event& e) = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

	virtual ~IGameState() {};
};