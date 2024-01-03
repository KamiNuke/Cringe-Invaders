#include "ExitState.h"

ExitState ExitState::sExitState;

ExitState* ExitState::Get()
{
    return &sExitState;
}

void ExitState::Enter()
{

}

void ExitState::Exit()
{

}

void ExitState::HandleEvent(SDL_Event& e)
{

}

void ExitState::Update()
{

}

void ExitState::Render() 
{

}