#pragma once
#include "SDL.h"
#include "IGameState.h"
#include "File.h"

extern SDL_Renderer* renderer;

extern IGameState* nextState;
extern IGameState* m_currentState;

extern File saveFile;

extern bool isHitboxes;

bool CollisionCheck(const SDL_Rect a, const SDL_Rect b);